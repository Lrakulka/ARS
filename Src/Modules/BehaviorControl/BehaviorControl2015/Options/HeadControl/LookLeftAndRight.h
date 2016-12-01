/**
 * Pun intended. Looks straight ahead in a way that the Nao V4's cameras
 * cover the area in front of its feet as well as everything
 * else in front of the robot.
 */
option(LookLeftAndRight, (float) (0.2f) tilt)
{
  initial_state(LookLeftAndRight)
  {
    transition
    {
	     if (state_time > 1000) { // After one second
		     goto lookLeft; // Robot starts looking left
       }
    }
    action
    {
      SetHeadPanTilt(0.f, tilt, 150_deg); // Look straight
    }
  }

  state(lookLeft)
  {
    transition
    {
    	if (state_time > 1000) { // After one second of looking left movement
    		goto lookRight; // Request looking right motion
    	}
    }
    action
    {
      SetHeadPanTilt(1.0f, tilt, 150_deg); // Look to the left
    }
  }

  state(lookRight)
  {
    transition
    {
    	if (state_time > 1000) { // After one second of looking right movement
    		goto lookLeft; // Request looking left motion
    	}
    }
    action
    {
      SetHeadPanTilt(-1.f, tilt, 150_deg); // Look to the right
    }
  }
}
