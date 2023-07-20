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
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

/*
 * When should you use the EXPECT_xxx or ASSERT_xxx macros?
 * Use ASSERT when failure should terminate processing, such as the reason for the test case.
 * Use EXPECT when failure should notify, but processing should continue
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
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0

    add_entries(1);

    // is the collection still empty?
    // if not empty, what must the size be?
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries

// TODO: Create a test to verify resizing increases the collection

// TODO: Create a test to verify resizing decreases the collection

// TODO: Create a test to verify resizing decreases the collection to zero

// TODO: Create a test to verify clear erases the collection

// TODO: Create a test to verify erase(begin,end) erases the collection

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
