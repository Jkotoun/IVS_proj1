//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Josef Kotoun <xkotou06@stud.fit.vutbr.cz>
// $Date:       $2020-02-16
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Josef Kotoun
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//
class EmptyTree : public ::testing::Test
{
    protected:
    BinaryTree tree = BinaryTree();
};
class NonEmptyTree : public EmptyTree
{
    protected:

    virtual void SetUp()
    {
        unsigned values[] = {10, 15, 40, 50, 12, 30};
        for(unsigned i = 0;i<sizeof(values)/sizeof(unsigned);i++)
        {
            tree.InsertNode(values[i]);
        }
    }
};
class TreeAxioms : public NonEmptyTree
{
    
};

TEST_F(EmptyTree, InsertNode)
{
      std::pair<bool, BinaryTree::Node_t *> val1 = tree.InsertNode(2);
      //zakladni hodnoty vlozeneho prvku
      ASSERT_TRUE(val1.second != NULL);
      EXPECT_TRUE(val1.second->key == 2);
      EXPECT_TRUE(val1.first);
      EXPECT_TRUE(val1.second == tree.GetRoot());
      EXPECT_TRUE(val1.second->pLeft != NULL);
      EXPECT_TRUE(val1.second->pRight != NULL);
      EXPECT_TRUE(val1.second->color == BinaryTree::BLACK);
      
      //levy list
      BinaryTree::Node_t * l_leaf = val1.second->pLeft;
      EXPECT_EQ(l_leaf->key, 0);
      EXPECT_TRUE(l_leaf->pLeft == nullptr);
      EXPECT_TRUE(l_leaf->pRight == nullptr);
      EXPECT_TRUE(l_leaf->pParent == val1.second);

      //pravy list
      BinaryTree::Node_t *r_leaf = val1.second->pRight;
      EXPECT_EQ(r_leaf->key, 0);
      EXPECT_TRUE(r_leaf->pLeft == nullptr);
      EXPECT_TRUE(r_leaf->pRight == nullptr);
      EXPECT_TRUE(r_leaf->pParent == val1.second);

      //vlozeni existujiciho
      std::pair<bool, BinaryTree::Node_t *>existing = tree.InsertNode(2);
      EXPECT_FALSE(existing.first);

      //vlozen vetsiho prvku doprava
      std::pair<bool, BinaryTree::Node_t*> val2 = tree.InsertNode(5);
      EXPECT_EQ(val1.second->pRight, val2.second);

      //vlozeni mensiho prvku doleva
      std::pair<bool, BinaryTree::Node_t*> val3 = tree.InsertNode(1);
      EXPECT_EQ(val1.second->pLeft, val3.second);
}
TEST_F(EmptyTree, DeleteNode)
{
    EXPECT_FALSE(tree.DeleteNode(10));
    EXPECT_FALSE(tree.DeleteNode(-10));
}
TEST_F(EmptyTree, FindNode)
{
    EXPECT_TRUE(tree.FindNode(10) == NULL);
    EXPECT_TRUE(tree.FindNode(0) == NULL);
}
TEST_F(NonEmptyTree, InsertNode)
{
    //vlozeni existujiciho
    std::pair<bool, BinaryTree::Node_t *> existing = tree.InsertNode(40);
    EXPECT_FALSE(existing.first);
    EXPECT_TRUE(tree.FindNode(40)!=NULL);
    EXPECT_TRUE(tree.FindNode(40) == existing.second);
    //vlozeni neexistujiciho
    EXPECT_TRUE(tree.FindNode(41) == NULL);
    std::pair<bool, BinaryTree::Node_t *> inserted = tree.InsertNode(41);
    EXPECT_TRUE(tree.FindNode(41)!= NULL);
}
TEST_F(NonEmptyTree, DeleteNode)
{
    //smazani existujiciho
    EXPECT_TRUE(tree.FindNode(15) != NULL);
    EXPECT_TRUE(tree.DeleteNode(15));
    EXPECT_TRUE(tree.FindNode(15) == NULL);
    EXPECT_FALSE(tree.DeleteNode(70));
}
TEST_F(NonEmptyTree, FindNode)
{   
    //existujici
    EXPECT_TRUE(tree.FindNode(40));
    BinaryTree::Node_t * node = tree.FindNode(40);
    EXPECT_TRUE(node->key == 40);

    //neexistujici
    EXPECT_TRUE(tree.FindNode(72) == NULL);
    EXPECT_TRUE(tree.FindNode(0) == NULL);
    EXPECT_TRUE(tree.FindNode(-5) == NULL);
}
TEST_F(TreeAxioms, Axiom1)
{
    std::vector<BinaryTree::Node_t*> leafs;
    tree.GetLeafNodes(leafs);
    for(unsigned i=0;i<leafs.size();i++)
    {
        EXPECT_TRUE(leafs[i]->color == BinaryTree::BLACK);
    }   
}
TEST_F(TreeAxioms, Axiom2)
{
    std::vector<BinaryTree::Node_t*> nodes;
    tree.GetNonLeafNodes(nodes);
    for(unsigned i=0;i<nodes.size();i++)
    {
        if(nodes[i]->color == BinaryTree::RED)
        {
            EXPECT_TRUE(nodes[i]->pLeft->color == BinaryTree::BLACK);
            EXPECT_TRUE(nodes[i]->pRight->color == BinaryTree::BLACK);
        }
    }
}
TEST_F(TreeAxioms, Axiom3)
{
    std::vector<BinaryTree::Node_t*> leafs;
    tree.GetLeafNodes(leafs);
    unsigned previousPathLength = -1;
    unsigned currentPathLength = 0;
    Node_t *currentNode;
    for(unsigned i=0;i<leafs.size();i++)
    {
        currentPathLength = 0;
        currentNode = leafs[i];
        while(currentNode)
        {
            if(currentNode->color == BinaryTree::BLACK)
            {
                currentPathLength++;
            }
            currentNode = currentNode->pParent;
        }
        if(previousPathLength != -1)
        {
            EXPECT_EQ(previousPathLength, currentPathLength);
        }
        previousPathLength = currentPathLength;
    }
}
/*** Konec souboru black_box_tests.cpp ***/
