#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  if (objects.size() == 0){
    this -> right = NULL;
    this -> left = NULL;
  }
  else if (objects.size() == 1){
    this -> left = objects[0];
    this -> right = NULL;
    insert_box_into_box(objects[0] -> box, this -> box);
  }
  else if (objects.size() == 2){
    this -> left = objects[0];
    this -> right = objects[1];
    insert_box_into_box(objects[0] -> box, this -> box);
    insert_box_into_box(objects[1] -> box, this -> box);
  }
  else{
    for (int i = 0; i < objects.size(); i++){
      //put them all into AABBTree
      insert_box_into_box(objects[i] -> box, this -> box);
    }
    //find axis
    double x = this->box.max_corner[0] - this->box.min_corner[0];
    double y = this->box.max_corner[1] - this->box.min_corner[1];
    double z = this->box.max_corner[2] - this->box.min_corner[2];
    int xyz;
    if (x > y && x > z){
      xyz = 0;
    }else if(y > x && y > z){
      xyz = 1;
    }else{
      xyz = 2;
    }
    double midpoint = (this->box.max_corner[xyz] + this->box.min_corner[xyz]) / 2.0;
    //create the left and right node
    std::vector<std::shared_ptr<Object>> left_node, right_node;
    //push the objects to two nodes
    for (int i = 0; i < objects.size(); i ++){
      if (objects[i] -> box.center()[xyz] < midpoint){
        left_node.push_back(objects[i]);
      }
      else{
        right_node.push_back(objects[i]);
      }
    }
    //now arrange the two temp nodes into the actual node
    if (left_node.size() == 0){
      this->left = right_node.back();
      right_node.pop_back();
    }
    else if(left_node.size() == 1){
      this -> left = left_node[0];
    }
    else{
      this -> left = std::make_shared<AABBTree>(left_node, depth+1);
    }
    //do the same thing for right node
    if (right_node.size() == 0){
      this->right = left_node.back();
      left_node.pop_back();
    }
    else if(right_node.size() == 1){
      this -> right = right_node[0];
    }
    else{
      this -> right = std::make_shared<AABBTree>(right_node, depth+1);
    }
  }
}













