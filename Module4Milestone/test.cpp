// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Eric Slutz
// SNHU - CS405 Secure Coding
// Module 4 Milestone
//

#include "pch.h"

// The global test environment setup and tear down.
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        // Initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// Test class to house shared data between tests.
class CollectionTest : public ::testing::Test
{
protected:
    // Create a smart point to hold the collection.
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    {
        // Create a new collection to be used in the test.
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    {
        // Erase all elements in the collection, if any remain.
        collection->clear();
        // Free the pointer.
        collection.reset(nullptr);
    }

    // Helper function to add random values from 0 to 99 count times to the collection.
    void add_entries(int count)
    {
        if (count > 0)
        {
            for (auto i = 0; i < count; ++i)
            {
                collection->push_back(rand() % 100);
            }
        }
    }
};

struct ParameterizedCollectionTest : CollectionTest, ::testing::WithParamInterface<int>
{
    ParameterizedCollectionTest() { }
};

INSTANTIATE_TEST_CASE_P(CollectionSizes, ParameterizedCollectionTest, ::testing::Values(0, 1, 5, 10));


/*
 * When should you use the EXPECT_xxx or ASSERT_xxx macros?
 * Use ASSERT when failure should terminate processing, such as the reason for the test case.
 * Use EXPECT when failure should notify, but processing should continue.
 * 
 * Prior to calling all TEST_F defined methods,
 * CollectionTest::StartUp is called.
 * 
 * Following this all TEST_F defined methods,
 * CollectionTest::TearDown is called
 */

// A collection smart pointer is not null.
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // Test that collection created.
    ASSERT_TRUE(collection);

    // Test that collection pointer is not equal to nullptr.
    ASSERT_NE(collection.get(), nullptr);
}

// A collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // Test that collection is empty.
    ASSERT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
//TEST_F(CollectionTest, AlwaysFail)
//{
//    FAIL();
//}

// Test to verify adding a single value to an empty collection.
TEST_F(CollectionTest, CanAddToEmptyCollection)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Add one element to the collection.
    add_entries(1);

    // Test that collection is not empty.
    ASSERT_FALSE(collection->empty());

    // Test that collection size is 1.
    ASSERT_EQ(collection->size(), 1);
}

// Test to verify adding five values to an empty collection.
TEST_F(CollectionTest, CanAddFiveValuesToCollection)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Add five elements to the collection.
    add_entries(5);

    // Test that collection is not empty.
    ASSERT_FALSE(collection->empty());

    // Test that collection size is 5.
    ASSERT_EQ(collection->size(), 5);
}

// Test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries.
TEST_P(ParameterizedCollectionTest, MaxSizeGreaterThanSize)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Add number of elements specified by the parameter to the collection.
    add_entries(GetParam());

    // Test that collection size matches parameter value.
    ASSERT_EQ(collection->size(), GetParam());

    // Test that collection max size is greater than collection size.
    ASSERT_GT(collection->max_size(), collection->size());
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_P(ParameterizedCollectionTest,CapacityGreaterThanOrEqualToSize)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Add number of elements specified by the parameter to the collection.
    add_entries(GetParam());

    // Test that collection size matches parameter value.
    ASSERT_EQ(collection->size(), GetParam());

    // Test that collection max size is greater than collection size.
    ASSERT_GE(collection->capacity(), collection->size());
}

// Test to verify resizing increases the collection.
TEST_F(CollectionTest, ResizeIncreasesCollectionSize)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Resize the collection to 5.
    collection->resize(5);

    // Test that collection size is increased to 5.
    ASSERT_EQ(collection->size(), 5);
}

// Test to verify resizing decreases the collection.
TEST_F(CollectionTest, ResizeDecreasesCollectionSize)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Add five elements to the collection.
    add_entries(5);

    // Test that collection is not empty.
    EXPECT_FALSE(collection->empty());

    // Test that collection size is 5.
    EXPECT_EQ(collection->size(), 5);

    // Resize the collection to 2.
    collection->resize(2);

    // Test that collection size decreased to 2.
    ASSERT_EQ(collection->size(), 2);
}

// Test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeCollectionSizeToZero)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Add five elements to the collection.
    add_entries(5);

    // Test that collection is not empty.
    EXPECT_FALSE(collection->empty());

    // Test that collection size is 5.
    EXPECT_EQ(collection->size(), 5);

    // Resize the collection to 0.
    collection->resize(0);

    // Test that collection size decreased to 0.
    ASSERT_EQ(collection->size(), 0);
}

// Test to verify clear erases the collection
TEST_F(CollectionTest, ClearCollection)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Add five elements to the collection.
    add_entries(5);

    // Test that collection is not empty.
    EXPECT_FALSE(collection->empty());

    // Test that collection size is 5.
    EXPECT_EQ(collection->size(), 5);

    // Clear the collection.
    collection->clear();

    // Test that collection is empty.
    ASSERT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    ASSERT_EQ(collection->size(), 0);
}

// Test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseCollection)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Add five elements to the collection.
    add_entries(5);

    // Test that collection is not empty.
    EXPECT_FALSE(collection->empty());

    // Test that collection size is 5.
    EXPECT_EQ(collection->size(), 5);

    // Erase the collection.
    collection->erase(collection->begin(), collection->end());

    // Test that collection is empty.
    ASSERT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    ASSERT_EQ(collection->size(), 0);
}

// Test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreaseCollectionCapacity)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Test that if collection empty, then capacity must be 0.
    EXPECT_EQ(collection->capacity(), 0);

    // Use reserve to increase the collection capacity.
    collection->reserve(5);

    // Test that collection is empty.
    ASSERT_TRUE(collection->empty());

    // Test that the size is still 0.
    ASSERT_EQ(collection->size(), 0);

    // Test that capacity is greater than size.
    ASSERT_GT(collection->capacity(), collection->size());
}
// Test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeExceptionThrown)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Test that expected exception is thrown.
    ASSERT_THROW(collection->at(5), std::out_of_range);
}

// Test to verify assign adds the specified number of elements and values.
TEST_F(CollectionTest, AssignValuesToCollection)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    collection->assign(5, 10);

    // Test that collection is not empty.
    ASSERT_FALSE(collection->empty());

    // Test that collection size is 5.
    ASSERT_EQ(collection->size(), 5);

    for (int i = 0; i < 5; i++)
    {
        ASSERT_EQ(collection->at(i), 10);
    }
}

// Test to verify collection cannot have a reserve larger than the collection max size.
// NOTE: This is a negative test
TEST_F(CollectionTest, IncreaseCollectionReserveAboveMaxSize)
{
    // Test that collection is empty.
    EXPECT_TRUE(collection->empty());

    // Test that if collection empty, then size must be 0.
    EXPECT_EQ(collection->size(), 0);

    // Test reserving a size larger than the max size od the collection.
    ASSERT_THROW(collection->reserve(collection->max_size() + 10), std::length_error);
}
