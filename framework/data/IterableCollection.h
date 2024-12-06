#ifndef ITERABLE_COLLECTION_H
#define ITERABLE_COLLECTION_H

#include <memory>
#include "Iterator.h"

/**
 * @interface IterableCollection
 * @brief Interface for collections that can provide iterators.
 */
class IterableCollection {
public:
    /**
     * @brief Factory method to create an iterator for the collection.
     * @return A unique pointer to an Iterator instance.
     */
    virtual std::unique_ptr<Iterator> create_iterator() const = 0;

    /**
     * @brief Virtual destructor for IterableCollection.
     */
    virtual ~IterableCollection() = default;
};

#endif // ITERABLE_COLLECTION_H
