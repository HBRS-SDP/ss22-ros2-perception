/*
 * Copyright 2016 Bonn-Rhein-Sieg University
 *
 * Author: Sergey Alexandrov
 * ROS2 contributors: Hamsa Datta Perur, Vamsi Kalagaturu.
 *
 */

#ifndef BOUNDING_BOX_VISUALIZER_HPP
#define BOUNDING_BOX_VISUALIZER_HPP

#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"
#include "rmw/qos_profiles.h"
#include "visualization_msgs/msg/marker.hpp"

#include "mas_perception_msgs/msg/bounding_box.hpp"
#include "mir_perception_utils/color.hpp"

#include "rmw/qos_profiles.h"

using mir_perception_utils::visualization::Color;

namespace mir_perception_utils
{
  namespace visualization
  {
    class BoundingBoxVisualizer
    {
      public:
        BoundingBoxVisualizer(const std::shared_ptr<rclcpp_lifecycle::LifecycleNode> &node,
                              const std::string &topic_name, Color color,
                              bool check_subscribers = true);

        BoundingBoxVisualizer(const std::string &topic_name, Color color,
                              bool check_subscribers = true);

        void publish(const mas_perception_msgs::msg::BoundingBox &box, const std::string &frame_id);

        void publish(const std::vector<mas_perception_msgs::msg::BoundingBox> &boxes, const std::string &frame_id);

        int getNumSubscribers();            

      private:
        rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_publisher_;
        const Color color_;
        bool check_subscribers_;
        rclcpp::QoS qos_default;
    };
  }
}
#endif /* BOUNDING_BOX_VISUALIZER_HPP */