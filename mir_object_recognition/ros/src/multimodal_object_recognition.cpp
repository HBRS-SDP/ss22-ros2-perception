
#include <std_msgs/msg/float64.hpp>

#include <mir_object_recognition/multimodal_object_recognition.hpp>

MultiModalObjectRecognitionROS2::MultiModalObjectRecognitionROS2(const std::string & node_name, bool intra_process_comms):
    rclcpp_lifecycle::LifecycleNode(node_name,
        rclcpp::NodeOptions().use_intra_process_comms(intra_process_comms))
{}

void MultiModalObjectRecognitionROS2::synchronizeCallback(const sensor_msgs::msg::Image image,
                      const sensor_msgs::msg::PointCloud2 cloud)
{

    RCLCPP_INFO(get_logger(), "synchro callback");

}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
MultiModalObjectRecognitionROS2::on_configure(const rclcpp_lifecycle::State &)
{
    // This callback is supposed to be used for initialization and
    // configuring purposes.
    // We thus initialize and configure our publishers and timers.
    // The lifecycle node API does return lifecycle components such as
    // lifecycle publishers. These entities obey the lifecycle and
    // can comply to the current state of the node.
    // As of the beta version, there is only a lifecycle publisher
    // available.
    
    RCLCPP_INFO(get_logger(), "on_configure() is called.");

    image_sub_.subscribe(this, "image");
    
    cloud_sub_.subscribe(this, "cloud");

    //msg_sync_.reset(new Sync(msgSyncPolicy(10), image_sub_, cloud_sub_));
    msg_sync_ = std::make_shared<Sync>(msgSyncPolicy(10), image_sub_, cloud_sub_);
    msg_sync_ -> registerCallback(&MultiModalObjectRecognitionROS2::synchronizeCallback, this);
    
    
    // We return a success and hence invoke the transition to the next
    // step: "inactive".
    // If we returned TRANSITION_CALLBACK_FAILURE instead, the state machine
    // would stay in the "unconfigured" state.
    // In case of TRANSITION_CALLBACK_ERROR or any thrown exception within
    // this callback, the state machine transitions to state "errorprocessing".
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
MultiModalObjectRecognitionROS2::on_activate(const rclcpp_lifecycle::State &)
{
    RCUTILS_LOG_INFO_NAMED(get_name(), "on_activate() is called.");

    // Let's sleep for 2 seconds.
    // We emulate we are doing important
    // work in the activating phase.
    std::this_thread::sleep_for(2s);

    // We return a success and hence invoke the transition to the next
    // step: "active".
    // If we returned TRANSITION_CALLBACK_FAILURE instead, the state machine
    // would stay in the "inactive" state.
    // In case of TRANSITION_CALLBACK_ERROR or any thrown exception within
    // this callback, the state machine transitions to state "errorprocessing".
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
MultiModalObjectRecognitionROS2::on_deactivate(const rclcpp_lifecycle::State &)
{
    RCUTILS_LOG_INFO_NAMED(get_name(), "on_deactivate() is called.");

    // We return a success and hence invoke the transition to the next
    // step: "inactive".
    // If we returned TRANSITION_CALLBACK_FAILURE instead, the state machine
    // would stay in the "active" state.
    // In case of TRANSITION_CALLBACK_ERROR or any thrown exception within
    // this callback, the state machine transitions to state "errorprocessing".
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
MultiModalObjectRecognitionROS2::on_cleanup(const rclcpp_lifecycle::State &)
{
    // In our cleanup phase, we release the shared pointers to the
    // timer and publisher. These entities are no longer available
    // and our node is "clean".
    // obj_list_pub_.reset();

    RCUTILS_LOG_INFO_NAMED(get_name(), "on cleanup is called.");

    // We return a success and hence invoke the transition to the next
    // step: "unconfigured".
    // If we returned TRANSITION_CALLBACK_FAILURE instead, the state machine
    // would stay in the "inactive" state.
    // In case of TRANSITION_CALLBACK_ERROR or any thrown exception within
    // this callback, the state machine transitions to state "errorprocessing".
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
MultiModalObjectRecognitionROS2::on_shutdown(const rclcpp_lifecycle::State & state)
{
    // In our shutdown phase, we release the shared pointers to the
    // timer and publisher. These entities are no longer available
    // and our node is "clean".
    // obj_list_pub_.reset();

    RCUTILS_LOG_INFO_NAMED(
      get_name(),
      "on shutdown is called from state %s.",
      state.label().c_str());

    // We return a success and hence invoke the transition to the next
    // step: "finalized".
    // If we returned TRANSITION_CALLBACK_FAILURE instead, the state machine
    // would stay in the current state.
    // In case of TRANSITION_CALLBACK_ERROR or any thrown exception within
    // this callback, the state machine transitions to state "errorprocessing".
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}


/**
 * A lifecycle node has the same node API
 * as a regular node. This means we can spawn a
 * node, give it a name and add it to the executor.
 */
int main(int argc, char * argv[])
{
  // force flush of the stdout buffer.
  // this ensures a correct sync of all prints
  // even when executed simultaneously within the launch file.
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);

  rclcpp::init(argc, argv);

  rclcpp::executors::SingleThreadedExecutor exe;

  std::shared_ptr<MultiModalObjectRecognitionROS2> mmor_lc_node =
    std::make_shared<MultiModalObjectRecognitionROS2>("multimodal_object_recognition", false);

  exe.add_node(mmor_lc_node->get_node_base_interface());

  exe.spin();

  rclcpp::shutdown();

  return 0;
}