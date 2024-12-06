#ifndef ITERATOR_H
#define ITERATOR_H

#include <vector>
#include <cstddef>

/**
 * @interface Iterator
 * @brief Interface for iterators.
 */
class Iterator {
public:
    /**
     * @brief Checks if there are more elements to be iterated.
     * @return True if there are more elements, false otherwise.
     */
    virtual bool has_more() const = 0;

    /**
     * @brief Returns the next element.
     * @return A reference to the next element.
     * @throws std::out_of_range if no more elements are available.
     */
    virtual const std::vector<long double>& get_next() = 0;

    /**
     * @brief Resets the iterator to the first element of the collection.
     */
    virtual void reset() = 0;

    /**
     * @brief Returns the number of elements in the collection.
     * @return Number of elements as a size_t.
     */
    virtual size_t size() const = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Iterator() = default;
};

#endif // ITERATOR_H
