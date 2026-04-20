#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"

// Empty tree!!
TEST(empty_tree) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0u);
    ASSERT_EQUAL(tree.height(), 0u);
    ASSERT_TRUE(tree.begin() == tree.end());
    ASSERT_TRUE(tree.min_element() == tree.end());
    ASSERT_TRUE(tree.max_element() == tree.end());
    ASSERT_TRUE(tree.find(1) == tree.end());
    ASSERT_TRUE(tree.min_greater_than(0) == tree.end());
}

// Single node
TEST(single_node) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 1u);
    ASSERT_EQUAL(tree.height(), 1u);
    ASSERT_EQUAL(*tree.min_element(), 5);
    ASSERT_EQUAL(*tree.max_element(), 5);
    ASSERT_TRUE(tree.find(5) != tree.end());
    ASSERT_TRUE(tree.find(99) == tree.end());
    ASSERT_TRUE(tree.min_greater_than(5) == tree.end());
    ASSERT_TRUE(tree.check_sorting_invariant());

    // check more find after adding more elements
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    ASSERT_EQUAL(*tree.find(5), 5);
    ASSERT_EQUAL(*tree.find(3), 3);
    ASSERT_EQUAL(*tree.find(7), 7);
    ASSERT_EQUAL(*tree.find(1), 1);
    ASSERT_EQUAL(*tree.find(4), 4);
    ASSERT_TRUE(tree.find(0) == tree.end());
    ASSERT_TRUE(tree.find(6) == tree.end());
}

// Left-skewed and right-skewed trees (for heights and extrema)
TEST(skewed_trees) {
    BinarySearchTree<int> left_skewed;
    left_skewed.insert(5);
    left_skewed.insert(3);
    left_skewed.insert(1);
    ASSERT_EQUAL(left_skewed.height(), 3u);
    ASSERT_EQUAL(left_skewed.size(), 3u);
    ASSERT_EQUAL(*left_skewed.min_element(), 1);
    ASSERT_EQUAL(*left_skewed.max_element(), 5);
    ASSERT_TRUE(left_skewed.check_sorting_invariant());

    BinarySearchTree<int> right_skewed;
    right_skewed.insert(1);
    right_skewed.insert(3);
    right_skewed.insert(5);
    ASSERT_EQUAL(right_skewed.height(), 3u);
    ASSERT_EQUAL(*right_skewed.min_element(), 1);
    ASSERT_EQUAL(*right_skewed.max_element(), 5);
    ASSERT_TRUE(right_skewed.check_sorting_invariant());
}

// traversals and iterator order
TEST(traversals_and_iterator) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);

    std::ostringstream inorder, preorder;
    tree.traverse_inorder(inorder);
    tree.traverse_preorder(preorder);
    ASSERT_EQUAL(inorder.str(), "1 2 3 4 6 ");
    ASSERT_EQUAL(preorder.str(), "4 2 1 3 6 ");

}

//copy ctor
TEST(copy_and_assign) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    BinarySearchTree<int> copy(tree);
    ASSERT_EQUAL(copy.size(), tree.size());
    ASSERT_EQUAL(copy.height(), tree.height());
    ASSERT_EQUAL(*copy.min_element(), *tree.min_element());
    ASSERT_EQUAL(*copy.max_element(), *tree.max_element());
    ASSERT_TRUE(copy.check_sorting_invariant());

    copy.insert(1);
    ASSERT_EQUAL(tree.size(), 3u);       // original 
    ASSERT_EQUAL(copy.size(), 4u);

    // exact structure 
    std::ostringstream orig_out, copy_out;
    tree.traverse_inorder(orig_out);
    copy.traverse_inorder(copy_out);
    ASSERT_EQUAL(orig_out.str(), "3 5 7 ");
    ASSERT_EQUAL(copy_out.str(), "1 3 5 7 ");
}

// check_sorting_invariant works
TEST(sorting_invariant_violated) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    ASSERT_TRUE(tree.check_sorting_invariant());

    // Break it 
    *tree.begin() = 10;  // min node (3) becomes 10
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(different_copies){
    // copy empty
    BinarySearchTree<int> empty;
    BinarySearchTree<int> empty_copy(empty);
    ASSERT_TRUE(empty_copy.empty());
    ASSERT_EQUAL(empty_copy.size(), 0u);

    // Copy single 
    BinarySearchTree<int> single;
    single.insert(5);
    BinarySearchTree<int> single_copy(single);
    ASSERT_EQUAL(single_copy.size(), 1u);
    ASSERT_EQUAL(*single_copy.min_element(), 5);
    std::ostringstream s1, s2;
    single.traverse_inorder(s1);
    single_copy.traverse_inorder(s2);
    ASSERT_EQUAL(s1.str(), s2.str());

    // Copy skewed
    BinarySearchTree<int> skewed;
    skewed.insert(1);
    skewed.insert(2);
    skewed.insert(3);
    BinarySearchTree<int> skewed_copy(skewed);
    std::ostringstream s3, s4;
    skewed.traverse_inorder(s3);
    skewed_copy.traverse_inorder(s4);
    ASSERT_EQUAL(s3.str(), s4.str());
    ASSERT_EQUAL(skewed_copy.height(), skewed.height());

}

TEST_MAIN()
