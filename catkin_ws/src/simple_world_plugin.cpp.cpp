#include <gazebo/common/Plugin.hh>
#include <ros/ros.h>


namespace gazebo {
	class worldPluginTutorial : public WorldPlugin {

	public: 

		WorldPluginTutorial() : WorldPlugin(){

		}

		void Load(physics::WorldPtr _world, sdf::elementPtr _sdf){
			//Make sure that ros is running
			if(!ros::isInitialized()){
				ROS_FATAL_STREAM("A ros node for gazebo has not been initialized, cannot load the plugin" << "Load the gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package)");
				return;
			}
			
			ROS_INFO("Hello_world");

		}

	};

	GZ_REGISTER_WORLD_PLUGIN(WorldPluginTutorial)s

}