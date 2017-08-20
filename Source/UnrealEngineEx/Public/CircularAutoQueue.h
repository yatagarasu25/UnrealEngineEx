// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once


/**
 * Implements a lock-free first-in first-out queue using a circular array with autorewrite.
 *
 * This class is not thread safe. Pushing to Full queue can cahnge Head position.
 *
 * The number of items that can be enqueued is one less than the queue's capacity,
 * because one item will be used for detecting full and empty states.
 *
 * @param ElementType The type of elements held in the queue.
 */
template<typename ElementType> class TCircularAutoQueue
{
public:
	TCircularAutoQueue()
		: Buffer(8)
		, Head(0)
		, Tail(0)
	{ }

	/**
	 * Default constructor.
	 *
	 * @param Size The number of elements that the queue can hold (will be rounded up to the next power of 2).
	 */
	TCircularAutoQueue(uint32 Size)
		: Buffer(Size)
		, Head(0)
		, Tail(0)
	{ }

	/** Virtual destructor. */
	virtual ~TCircularAutoQueue() { }

public:

	void Reset(uint32 Size)
	{
		Buffer = TCircularBuffer<ElementType>(Size);
		Head = 0;
		Tail = 0;
	}

	/**
	 * Gets the number of elements in the queue.
	 *
	 * @return Number of queued elements.
	 */
	uint32 Count() const
	{
		int32 Count = Tail - Head;

		if (Count < 0)
		{
			Count += Buffer.Capacity();
		}

		return Count;
	}

	/**
	 * Removes an item from the front of the queue.
	 *
	 * @param OutElement Will contain the element if the queue is not empty.
	 * @return true if an element has been returned, false if the queue was empty.
	 */
	bool Dequeue(ElementType& OutElement)
	{
		if (Head != Tail)
		{
			OutElement = Buffer[Head];
			Head = Buffer.GetNextIndex(Head);

			return true;
		}

		return false;
	}

	/**
	 * Empties the queue.
	 *
	 * @see IsEmpty
	 */
	void Empty()
	{
		Head = Tail;
	}

	/**
	 * Adds an item to the end of the queue.
	 *
	 * @param Element The element to add.
	 * @return true if the item was added, false if the queue was full.
	 */
	bool Enqueue(const ElementType& Element)
	{
		uint32 NewTail = Buffer.GetNextIndex(Tail);

		if (NewTail == Head)
		{
			Head = Buffer.GetNextIndex(Head);
		}

		Buffer[Tail] = Element;
		Tail = NewTail;

		return true;
	}

	/**
	 * Checks whether the queue is empty.
	 *
	 * @return true if the queue is empty, false otherwise.
	 * @see Empty, IsFull
	 */
	FORCEINLINE bool IsEmpty() const
	{
		return (Head == Tail);
	}

	/**
	 * Checks whether the queue is full.
	 *
	 * @return true if the queue is full, false otherwise.
	 * @see IsEmpty
	 */
	bool IsFull() const
	{
		return (Buffer.GetNextIndex(Tail) == Head);
	}

	/**
	 * Returns the oldest item in the queue without removing it.
	 *
	 * @param OutItem Will contain the item if the queue is not empty.
	 * @return true if an item has been returned, false if the queue was empty.
	 */
	bool PeekHead(ElementType& OutItem) const
	{
		if (Head != Tail)
		{
			OutItem = Buffer[Head];

			return true;
		}

		return false;
	}

	/**
	* Returns the newest item in the queue without removing it.
	*
	* @param OutItem Will contain the item if the queue is not empty.
	* @return true if an item has been returned, false if the queue was empty.
	*/
	bool PeekTail(ElementType& OutItem) const
	{
		if (Head != Tail)
		{
			OutItem = Buffer[Buffer.GetPreviousIndex(Tail)];

			return true;
		}

		return false;
	}

private:

	/** Holds the buffer. */
	TCircularBuffer<ElementType> Buffer;

	/** Holds the index to the first item in the buffer. */
	MS_ALIGN(PLATFORM_CACHE_LINE_SIZE) volatile uint32 Head GCC_ALIGN(PLATFORM_CACHE_LINE_SIZE);

	/** Holds the index to the last item in the buffer. */
	MS_ALIGN(PLATFORM_CACHE_LINE_SIZE) volatile uint32 Tail GCC_ALIGN(PLATFORM_CACHE_LINE_SIZE);
};
