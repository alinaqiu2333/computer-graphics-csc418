#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> queue;
  if (box_box_intersect(rootA -> box, rootB -> box)){
     queue.push_back(std::make_pair(rootA, rootB));
  }
  std::shared_ptr<Object> node_A, node_B;
  std::shared_ptr<AABBTree> tree_A, tree_B;
  while (!queue.empty()){
    //get the first pair on top of queue
    node_A = queue.front().first;
    node_B = queue.front().second;
    queue.pop_front();
    tree_A = std::dynamic_pointer_cast<AABBTree>(node_A);
    tree_B = std::dynamic_pointer_cast<AABBTree>(node_B);
    if (tree_A == NULL && tree_B == NULL){
      leaf_pairs.emplace_back(std::make_pair(node_A, node_B));
    }
    //where A is a leaf but B is a tree
    else if (tree_A == NULL){
      //leaf A and treeB left
      if (box_box_intersect(node_A -> box, tree_B -> left -> box)){
        queue.push_back(std::make_pair(node_A, tree_B -> left));
      }
      //leaf A and treeB right
      if (box_box_intersect(node_A -> box, tree_B -> right -> box)){
        queue.push_back(std::make_pair(node_A, tree_B -> right));
      }
    }
    else if (tree_B == NULL){
      //leaf B and treeA left
      if (box_box_intersect(node_B -> box, tree_A -> left -> box)){
        queue.push_back(std::make_pair(tree_A -> left, node_B));
      }
      //leaf B and treeA right
      if (box_box_intersect(node_B -> box, tree_A -> right -> box)){
        queue.push_back(std::make_pair(tree_A -> right, node_B));
      }
    }
    //both are trees
    else{
      //albl
      if (box_box_intersect(tree_A -> left -> box, tree_B -> left -> box)){
        queue.push_back(std::make_pair(tree_A -> left, tree_B -> left));
      }
      //albr
      if (box_box_intersect(tree_A -> left -> box, tree_B -> right -> box)){
        queue.push_back(std::make_pair(tree_A -> left, tree_B -> right));
      }
      //arbr
      if (box_box_intersect(tree_A -> right -> box, tree_B -> right -> box)){
        queue.push_back(std::make_pair(tree_A -> right, tree_B -> right));
      }
      //arbl
      if (box_box_intersect(tree_A -> right -> box, tree_B -> left -> box)){
        queue.push_back(std::make_pair(tree_A -> right, tree_B -> left));
      }
    }

  }

}
