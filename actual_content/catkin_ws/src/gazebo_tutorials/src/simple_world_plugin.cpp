#include <gazebo/physics/physics.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/Model.hh>
#include <ros/ros.h>
#include <ros/subscribe_options.h>
#include <ros/console.h>
#include <ros/callback_queue.h>
#include <std_msgs/Float64.h>
#include <thread>


namespace gazebo {
	class ModelPluginTutorial : public ModelPlugin {

	public: 

		ModelPluginTutorial() : ModelPlugin(){

		}

		void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf){
			//Make sure that ros is running
			if(!ros::isInitialized()){
				int argc = 0;
				char **argv = NULL;
				ros::init(argc,argv,"gazebo_client",ros::init_options::NoSigintHandler);
			}

			ROS_INFO("Creating the plugin");

			//locally store the model
			this->model = _model;

			//Store the joint so that you can use it for torque control
			//Need to get the revolute joint name
			this->revolute_joint = _model->GetJoint("spinner");


			//setup the boring ros stuff
			//Create a node handle to manage communication
			this->rosNode = new ros::NodeHandle("gazebo_client");

			this->rosSub = this->rosNode->subscribe("pendulum_torque",100,&ModelPluginTutorial::controller_callback, this);

			ROS_INFO("You should have the plugin by now");

			//Create the ros Thread
			//this->rosQueueThread = std::thread(std::bind(ModelPluginTutorial::QueueThread, this));
		}



		void controller_callback(const std_msgs::Float64ConstPtr &  _msg){
			this->revolute_joint->SetForce(0,_msg->data);
		}





	private:
		physics::JointPtr revolute_joint;
		physics::ModelPtr model;
		ros::NodeHandle* rosNode;
		ros::Subscriber rosSub;
		ros::CallbackQueue rosQueue;
        std::thread rosQueueThread;

		void QueueThread(){
			static const double timeout = 0.01;
			while(this->rosNode->ok()){
				//this->rosQueueCallAvailable(ros::WallDuration(timeout));
			}
		}


	};

	GZ_REGISTER_MODEL_PLUGIN(ModelPluginTutorial)

}