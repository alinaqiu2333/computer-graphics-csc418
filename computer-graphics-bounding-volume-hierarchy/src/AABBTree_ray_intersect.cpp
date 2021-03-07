#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{//base case
  if (this -> num_leaves == 0){
    return false;
  }
  
  //no intersection
  bool if_hit = ray_intersect_box(ray, this -> box, min_t, max_t);
  if (!if_hit){
    return false;
  }
  else{
    //induction step, which is when a hit occurs
    double t1, t2;
    std::shared_ptr<Object> left_child, right_child;
    bool left_hit = this -> left != NULL && this -> left -> ray_intersect(ray, min_t, max_t, t1, left_child);
    bool right_hit = this -> right != NULL && this -> right -> ray_intersect(ray, min_t, max_t, t2, right_child);
    //a hit was occured at left, but left node is a leaf
    if (left_child == NULL && left_hit){
      left_child = this -> left;
    }
    if (right_child == NULL && right_hit){
      right_child = this -> right;
    }
    if (left_hit && right_hit){
      t = fmin(t1, t2);
      if (t == t1){
        descendant = left_child;
        return true;
      }
      else {
        descendant = right_child;
        return true;
      }
    }
    else if (right_hit){
      t = t2;
      descendant = right_child;
      return true;
    }
    else if (left_hit){
      t = t1;
      descendant = left_child;
      return true;
    }
    else{
      return false; 
    }
  }
  return false;
}
