#include <lib/bst.h>
#include <gtest/gtest.h>


std::vector<int> traversal(bst<int>& tree, inorder type) {
    std::vector<int> result;
    for(auto it = tree.begin<inorder>(); it != tree.end<inorder>(); ++it) {
        result.push_back(*it);
    }
    return result;
}

std::vector<int> traversal(bst<int>& tree, preorder type) {
    std::vector<int> result;
    for(auto it = tree.begin<preorder>(); it != tree.end<preorder>(); ++it) {
        result.push_back(*it);
    }
    return result;
}

std::vector<int> traversal(bst<int>& tree, postorder type) {
    std::vector<int> result;
    for(auto it = tree.begin<postorder>(); it != tree.end<postorder>(); ++it) {
        result.push_back(*it);
    }
    return result;
}

std::vector<int> reverse_traversal(bst<int>& tree, preorder type) {
    std::vector<int> result;
    for(auto it = tree.end<preorder>(); it != tree.begin<preorder>();) {
        --it;
        result.push_back(*it);
    }
    return result;
}

std::vector<int> reverse_traversal(bst<int>& tree, postorder type) {
    std::vector<int> result;
    for(auto it = tree.end<postorder>(); it != tree.begin<postorder>();) {
        --it;
        result.push_back(*it);
    }
    return result;
}

std::vector<int> reverse_traversal(bst<int>& tree, inorder type) {
    std::vector<int> result;
    for(auto it = tree.end<inorder>(); it != tree.begin<inorder>();) {
        --it;
        result.push_back(*it);
    }
    return result;
}

std::vector<int> rtraversal(bst<int>& tree, inorder type) {
    std::vector<int> result;
    for(auto it = tree.rbegin<inorder>(); it != tree.rend<inorder>(); ++it) {
        result.push_back(*it);
    }
    return result;
}

std::vector<int> reverse_rtraversal(bst<int>& tree, inorder type) {
    std::vector<int> result;
    for(auto it = tree.rend<inorder>(); it != tree.rbegin<inorder>();) {
        --it;
        result.push_back(*it);
    }
    return result;
}


TEST(BSTestSuite, EmptyTest) {
    bst<int> a;
    ASSERT_TRUE(a.empty());
}

TEST(BSTestSuite, NonEmptyTest) {
    bst<int> a;
    a.insert(1);
    ASSERT_FALSE(a.empty());
}

TEST(BSTestSuite, SizeTest) {
    bst<int> a;
    ASSERT_EQ(a.size(), 0);
    a.insert(1);
    ASSERT_EQ(a.size(), 1);
}

TEST(BSTestSuite, InorderTest) {
    bst<int> a{17, 50, 74, 32, 89, 5, 61, 29, 43, 99, 10, 68, 22, 36, 83, 55, 7, 91, 14, 66};
    inorder i;
    std::vector<int> expected = {5, 7, 10, 14, 17, 22, 29, 32, 36, 43, 50, 55, 61, 66, 68, 74, 83, 89, 91, 99};
    ASSERT_EQ(traversal(a, i), expected);
}

TEST(BSTestSuite, PreorderTest) {
    bst<int> a{17, 50, 74, 32, 89, 5, 61, 29, 43, 99, 10, 68, 22, 36, 83, 55, 7, 91, 14, 66};
    preorder p;
    std::vector<int> expected = {17, 5, 10, 7, 14, 50, 32, 29, 22, 43, 36, 74, 61, 55, 68, 66, 89, 83, 99, 91};
    ASSERT_EQ(traversal(a, p), expected);
}

TEST(BSTestSuite, PostorderTest) {
    bst<int> a{17, 50, 74, 32, 89, 5, 61, 29, 43, 99, 10, 68, 22, 36, 83, 55, 7, 91, 14, 66};
    postorder po;
    std::vector<int> expected = {7, 14, 10, 5, 22, 29, 36, 43, 32, 55, 66, 68, 61, 83, 91, 99, 89, 74, 50, 17};
    ASSERT_EQ(traversal(a, po), expected);
}

TEST(BSTestSuite, ReverseInorderTest) {
    bst<int> a{17, 50, 74, 32, 89, 5, 61, 29, 43, 99, 10, 68, 22, 36, 83, 55, 7, 91, 14, 66};
    inorder ri;
    std::vector<int> expected = {99, 91, 89, 83, 74, 68, 66, 61, 55, 50, 43, 36, 32, 29, 22, 17, 14, 10, 7, 5};
    ASSERT_EQ(reverse_traversal(a, ri), expected);
}

TEST(BSTestSuite, ReversePreorderTest) {
    bst<int> a{17, 50, 74, 32, 89, 5, 61, 29, 43, 99, 10, 68, 22, 36, 83, 55, 7, 91, 14, 66};
    preorder rp;
    std::vector<int> expected = {91, 99, 83, 89, 66, 68, 55, 61, 74, 36, 43, 22, 29, 32, 50, 14, 7, 10, 5, 17};
    ASSERT_EQ(reverse_traversal(a, rp), expected);
}

TEST(BSTestSuite, ReversePostorderTest) {
    bst<int> a{17, 50, 74, 32, 89, 5, 61, 29, 43, 99, 10, 68, 22, 36, 83, 55, 7, 91, 14, 66};
    postorder rp;
    std::vector<int> expected = {17, 50, 74, 89, 99, 91, 83, 61, 68, 66, 55, 32, 43, 36, 29, 22, 5, 10, 14, 7};
    ASSERT_EQ(reverse_traversal(a, rp), expected);
}

TEST(BSTestSuite, EraseTest) {
    bst<int> a = bst<int>({5, 12, 8, 36, 20, 3, 17, 9, 25, 14});
    ASSERT_EQ(a.size(), 10);
    a.erase(5);
    a.erase(12);
    a.erase(9);
    ASSERT_EQ(a.size(), 7);
    inorder i;
    std::vector<int> expected = {3, 8, 14, 17, 20, 25, 36};
    ASSERT_EQ(traversal(a, i), expected);
}

TEST(BSTestSuite, EraseAllTest) {
    bst<int> a = bst<int>({5, 12, 8, 36, 20, 3, 17, 9, 25, 14});
    ASSERT_EQ(a.size(), 10);
    a.erase(5);
    a.erase(12);
    a.erase(8);
    a.erase(36);
    a.erase(20);
    a.erase(3);
    a.erase(17);
    a.erase(9);
    a.erase(25);
    a.erase(14);
    ASSERT_EQ(a.size(), 0);
    inorder i;
    std::vector<int> expected = {};
    ASSERT_EQ(traversal(a, i), expected);
    ASSERT_TRUE(a.empty());
}

TEST(BSTestSuite, EraseRange) {
    bst<int> a = bst<int>({5, 12, 8, 36, 20, 3, 17, 9, 25, 14});
    ASSERT_EQ(a.size(), 10);
    auto q1 = a.begin();
    auto q2 = q1;
    q2++;
    q2++;
    q2++;
    a.erase(q1, q2);
    inorder i;
    std::vector<int> expected = {9, 12, 14, 17, 20, 25, 36};
    ASSERT_EQ(traversal(a, i), expected);
}


TEST(BSTestSuite, ClearTest) {
    bst<int> a = bst<int>({5, 12, 8, 36, 20, 3, 17, 9, 25, 14});
    ASSERT_EQ(a.size(), 10);
    a.clear();
    ASSERT_EQ(a.size(), 0);
    inorder i;
    std::vector<int> expected = {};
    ASSERT_EQ(traversal(a, i), expected);
    ASSERT_TRUE(a.empty());
}

TEST(BSTestSuite, InsertRange) {
    bst<int> a{1, 2, 3};
    bst<int> b{4, 5, 6};
    a.insert(b.begin(), b.end());
    inorder i;
    std::vector<int> expected = {1, 2, 3, 4, 5, 6};
    ASSERT_EQ(traversal(a, i), expected);
}

TEST(BSTestSuite, FindTest) {
    bst<int> a = bst<int>({5, 12, 8, 36, 20, 3, 17, 9, 25, 14});
    ASSERT_EQ(*a.find(5), 5);
    ASSERT_EQ(*a.find(12), 12);    
    ASSERT_EQ(*a.find(8), 8);
    ASSERT_EQ(*a.find(36), 36);
    ASSERT_EQ(*a.find(20), 20);
    ASSERT_EQ(*a.find(3), 3);
    ASSERT_EQ(*a.find(17), 17);
    ASSERT_EQ(*a.find(9), 9);
    ASSERT_EQ(*a.find(25), 25);
    ASSERT_EQ(*a.find(14), 14);   
    ASSERT_EQ(a.find(100), a.end());
    ASSERT_EQ(a.find(-1), a.end());
}

TEST(BSTestSuite, UpperBoundTest) {
    bst<int> a = bst<int>({5, 12, 8, 36, 20, 3, 17, 9, 25, 14});
    ASSERT_EQ(*a.upper_bound(5), 8);
    ASSERT_EQ(*a.upper_bound(12), 14);
    ASSERT_EQ(*a.upper_bound(8), 9);
    ASSERT_EQ(*a.upper_bound(20), 25);
    ASSERT_EQ(*a.upper_bound(3), 5);
    ASSERT_EQ(*a.upper_bound(17), 20);
    ASSERT_EQ(*a.upper_bound(9), 12);
    ASSERT_EQ(*a.upper_bound(25), 36);
    ASSERT_EQ(*a.upper_bound(14), 17);
    ASSERT_EQ(*a.upper_bound(-1), 3);  
    ASSERT_TRUE(a.upper_bound(36) == a.end());
    ASSERT_TRUE(a.upper_bound(100) == a.end());
}

TEST(BSTestSuite, LowerBoundTest) {
    bst<int> a = bst<int>({5, 12, 8, 36, 20, 3, 17, 9, 25, 14});
    ASSERT_EQ(*a.lower_bound(5), 3);
    ASSERT_EQ(*a.lower_bound(12), 9);
    ASSERT_EQ(*a.lower_bound(8), 5);
    ASSERT_EQ(*a.lower_bound(20), 17);
    ASSERT_EQ(*a.lower_bound(17), 14);
    ASSERT_EQ(*a.lower_bound(9), 8);
    ASSERT_EQ(*a.lower_bound(25), 20);
    ASSERT_EQ(*a.lower_bound(14), 12);
    ASSERT_EQ(*a.lower_bound(100), 36);
    ASSERT_TRUE(a.lower_bound(3) == a.end());
    ASSERT_TRUE(a.lower_bound(-1) == a.end());
}

TEST(BSTestSuite, ReverseIteratorTest) {
    bst<int> a = bst<int>({5, 12, 8, 36, 20, 3, 17, 9, 25, 14});
    inorder i;
    std::vector<int> expected = {36, 25, 20, 17, 14, 12, 9, 8, 5, 3};
    ASSERT_EQ(rtraversal(a, i), expected);
}

TEST(BSTestSuite, ReverseEndToBeginTest) {
    bst<int> a = bst<int>({5, 12, 8, 36, 20, 3, 17, 9, 25, 14});
    inorder i;
    std::vector<int> expected = {3, 5, 8, 9, 12, 14, 17, 20, 25, 36};
    ASSERT_EQ(reverse_rtraversal(a, i), expected);
}
