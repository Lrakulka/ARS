/** Pun intended. Looks straight ahead in a way that the Nao V4's cameras cover the area in front of its feet as well as everything else in front of the robot.*/
option(LookLeftAndRight, (float) (0.2f) tilt)
{
  initial_state(LookLeftAndRight)
  {
    transition
    {
	if (state_time > 1000) {
		goto lookLeft;
        }
    }
    action
    {
      SetHeadPanTilt(0.f, tilt, 150_deg);
    }
  }

  state(lookLeft)
  {
    transition
    {
	if (state_time > 1000) {
		goto lookRight;
	}
    }
    action
    {
      SetHeadPanTilt(1.0f, tilt, 150_deg);
    }
  }

  state(lookRight)
  {
    transition
    {
	if (state_time > 1000) {
		goto lookLeft;
	}
    }
    action
    {
      SetHeadPanTilt(-1.f, tilt, 150_deg);
    }
  }
}
