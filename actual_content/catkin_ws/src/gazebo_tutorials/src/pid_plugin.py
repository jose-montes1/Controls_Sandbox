import rospy
from gazebo_msgs.msg import LinkStates

#Get some plotting in
import matplotlib.pyplot as plt
import matplotlib.animation as animatoin
from matplotlib import style






def pose_callback(msg):
	spinner_link_index = msg.name.index('Pendulum_V3::link_3')
	print(msg.twist[spinner_link_index].angular.z)
	#print(dir(msg))

rospy.init_node("pose listener")
spinner_pose = rospy.Subscriber("/gazebo/link_states", LinkStates, pose_callback)
rospy.spin()