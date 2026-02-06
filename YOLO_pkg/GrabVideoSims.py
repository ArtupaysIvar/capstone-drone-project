#!/usr/bin/env python3

# import os
import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

# import cv2
# import numpy as np
from ultralytics import YOLO

from pixel_msgs.msg import PixelCoordinates
from ament_index_python.packages import get_package_share_directory


class GrabVideo(Node):

    def __init__(self):
        super().__init__('grab_video')

        self.model = YOLO('yolov8n.pt')
        self.bridge = CvBridge()

        # subscription
        self.subscription1 = self.create_subscription(
            Image, 'camera_drone1', 
            self.drone1_cam_callback, 10)

        self.subscription2 = self.create_subscription(
            Image, 'camera_drone2', 
            self.drone2_cam_callback, 10)

        self.subscription3 = self.create_subscription(
            Image, 'camera_drone3', 
            self.drone3_cam_callback, 10)
        
        # publishers
        self.publisher_1 = self.create_publisher(
            PixelCoordinates, 'pixel_topic1', 10)
        
        self.publisher_2 = self.create_publisher(
            PixelCoordinates, 'pixel_topic2', 10)
        
        self.publisher_3 = self.create_publisher(
            PixelCoordinates, 'pixel_topic3', 10)

        # timer
        self.timer = self.create_timer(0.5, self.timer_callback)

    def drone1_cam_callback(self, data_cam1):    
        # convert ROS Image message to OpenCV image
        current_frame1 = self.bridge.imgmsg_to_cv2(data_cam1, desired_encoding="bgr8")
        results1 = self.model.predict(current_frame1, classes=[0, 2])

        if len(results1[0].boxes) > 0:
            x_mid1, y_mid1, width1, height1 = results1[0].boxes.xywh[0]
            confidence1 = results1[0].boxes.conf

            self.det1 = (int(x_mid1), int(y_mid1), confidence1, width1)
        # boxes = results[0].boxes.xywh
        # confidences = results[0].boxes.conf

        # if boxes & confidences is not None:
        #     for box, conf in zip(boxes, confidences):
        #         x_mid1, y_mid1, width1, height1 = box
        #         curr_conf = conf

    def drone2_cam_callback(self, data_cam2):
        current_frame2 = self.bridge.imgmsg_to_cv2(data_cam2, desired_encoding="bgr8")
        results2 = self.model.predict(current_frame2, classes=[0, 2])
        if len(results2[0].boxes) > 0:
            x_mid2, y_mid2, width2, height2 = results2[0].boxes.xywh[0]
            confidence2 = results2[0].boxes.conf

            self.det2 = (int(x_mid2), int(y_mid2), confidence2)

    def drone3_cam_callback(self, data_cam3):
        current_frame3 = self.bridge.imgmsg_to_cv2(data_cam3, desired_encoding="bgr8")
        results3 = self.model.predict(current_frame3, classes=[0, 2])
        if len(results3[0].boxes) > 0:
            x_mid3, y_mid3, width3, height3 = results3[0].boxes.xywh[0]
            confidence3 = results3[0].boxes.conf

            self.det3 = (int(x_mid3), int(y_mid3), confidence3)

    def timer_callback(self):
        now = self.get_clock().now().to_msg()

        if self.det1 is not None:
            x, y, conf = self.det1
            msg = PixelCoordinates()
            msg.header.stamp = now
            msg.u = x
            msg.v = y
            msg.confidence = conf
            self.publisher_1.publish(msg)

        if self.det2 is not None:
            x, y, conf = self.det2
            msg = PixelCoordinates()
            msg.header.stamp = now
            msg.u = x
            msg.v = y
            msg.confidence = conf
            self.publisher_2.publish(msg)

        if self.det3 is not None:
            x, y, conf = self.det3
            msg = PixelCoordinates()
            msg.header.stamp = now
            msg.u = x
            msg.v = y
            msg.confidence = conf
            self.publisher_3.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = GrabVideo()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
