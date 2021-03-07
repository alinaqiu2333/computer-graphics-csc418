#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  //initialize the queue
  std::priority_queue<std:: pair<double, std::shared_ptr<Object>>, 
                      std::vector<std:: pair<double, std::shared_ptr<Object>>>, 
                      std::greater<std:: pair<double, std::shared_ptr<Object>>> > p_queue;
  double abs_min = std::numeric_limits<double>::infinity();
  double curr_distance =  point_box_squared_distance(query, root -> box);
  p_queue.push(std::make_pair(curr_distance, root));
  //initialize a node pointer
  std:: pair<double, std::shared_ptr<Object>> curr_queue_node;
  while (!p_queue.empty()){
    curr_queue_node = p_queue.top();
    double distance = curr_queue_node.first;
    std::shared_ptr<Object> curr_tree = curr_queue_node.second;
    p_queue.pop();
    std::shared_ptr<AABBTree> temp_tree = std::dynamic_pointer_cast<AABBTree> (curr_tree);
    if (distance < abs_min){
      //check if not empty
      if (temp_tree != NULL){
        double left_distance, right_distance;
        left_distance = point_box_squared_distance(query, temp_tree -> left -> box);
        right_distance = point_box_squared_distance(query, temp_tree -> right -> box);
        p_queue.push(std::make_pair(left_distance, temp_tree->left));
        p_queue.push(std::make_pair(right_distance, temp_tree->right));
      }
      else{
        double updated_sqrd;
        std::shared_ptr<Object> updated_descendant;
        if (curr_tree -> point_squared_distance(query, min_sqrd, max_sqrd, updated_sqrd, updated_descendant)){
          if (updated_sqrd < abs_min){
            abs_min = updated_sqrd;
            descendant = curr_tree;
          }
        }
      }
    }
  }
  if (!isinf(abs_min)){
    sqrd = abs_min;
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////
}
