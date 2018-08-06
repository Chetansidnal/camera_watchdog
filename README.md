# camera_watchdog
monitors the camera by subscribing camera topic

it includes diaglib , publishes its status on `tcp://*:5563`
In order to read the publisher one has to subscribe to the port number mention in the congif.json file

You need to launch this node saperately any time. 
