#include "../source/OrderStatsTree.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

using namespace ToopLoox;

namespace
{


using Tree = OrderStatsTree<int>;

struct NodeCallback
{
    void operator()(int key, int parent, unsigned height, unsigned count, unsigned countRecursive, Tree::NodeType type) const
    {
        onEntry(key, parent, height, count, countRecursive, type);
    }

    MOCK_CONST_METHOD6(onEntry, void(int, int, unsigned, unsigned, unsigned, Tree::NodeType));
};

}


TEST(OrderStatsTreeTest, TreeTest) 
{
    Tree tree;
    tree.add(5);
    tree.add(8);
    tree.add(12);
    tree.add(3);
    tree.add(1);
    tree.add(0);

    EXPECT_EQ(6, tree.getSize());
    ::testing::StrictMock<NodeCallback> callback;

    ::testing::InSequence seq;
    EXPECT_CALL(callback, onEntry(3, 3, 3, 1, 6, Tree::NodeType::ROOT)); 
    EXPECT_CALL(callback, onEntry(1, 3, 2, 1, 2, Tree::NodeType::LEFT)); 
    EXPECT_CALL(callback, onEntry(0, 1, 1, 1, 1, Tree::NodeType::LEFT)); 
    EXPECT_CALL(callback, onEntry(8, 3, 2, 1, 3, Tree::NodeType::RIGHT)); 
    EXPECT_CALL(callback, onEntry(5, 8, 1, 1, 1, Tree::NodeType::LEFT)); 
    EXPECT_CALL(callback, onEntry(12, 8, 1, 1, 1, Tree::NodeType::RIGHT)); 

    //     3
    //   1   8    
    // 0   5   12

    tree.forEachPreorder(callback);
}


TEST(OrderStatsTreeTest, DuplicatesTest) 
{
    Tree tree;
    tree.add(5);
    tree.add(1);
    tree.add(2);
    tree.add(5);
    tree.add(1);
    tree.add(1);

    EXPECT_EQ(6, tree.getSize());
    ::testing::StrictMock<NodeCallback> callback;

    EXPECT_CALL(callback, onEntry(2, 2, 2, 1, 6, Tree::NodeType::ROOT)); 
    EXPECT_CALL(callback, onEntry(1, 2, 1, 3, 3, Tree::NodeType::LEFT)); 
    EXPECT_CALL(callback, onEntry(5, 2, 1, 2, 2, Tree::NodeType::RIGHT)); 

    //     2
    //   1   5    

    tree.forEachPreorder(callback);        
}

TEST(OrderStatsTreeTest, AccessTest) 
{
    std::vector<int> numbers;
    Tree tree;
    for (int i = 0; i < 100; ++i)
    {
        numbers.push_back(rand() % 50);
        tree.add(numbers.back());
    }

    std::sort(numbers.begin(), numbers.end());

    ASSERT_EQ(numbers.size(), tree.getSize());
    for (int i = 0; i < numbers.size(); ++i)
    {
        ASSERT_EQ(numbers[i], tree[i]);
    }
}

