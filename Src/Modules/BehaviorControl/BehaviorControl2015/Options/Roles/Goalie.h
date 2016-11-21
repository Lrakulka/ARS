/** A test goalie option without common decision */
option(Goalie)
{

initial_state(start)
  {
    transition
    {
      if(state_time > 1000)
        goto lookAround;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      Stand();
    }
  }

state(lookAround)
  {
    transition
    {
        if(libCodeRelease.timeSinceBallWasSeen() < 300)
        goto trackTheBall;
    }
    action
    {
      theHeadControlMode = HeadControl::lookLeftAndRight;
    }
  }

state(trackTheBall)
  {
    int shotDetected = 0;
    float op = theBallModel.estimate.position.norm();
    float np = theBallModel.estimate.position.norm();

    transition
    {
      if(libCodeRelease.timeSinceBallWasSeen() > 7000)
        goto lookAround;

      if(shotDetected)
        goto defendTheShot;

      if(theBallModel.estimate.position.norm() < 1000.f)
	goto defendTheShot;
    }
    action
    {
      op = np;
      np = theBallModel.estimate.position.norm();

    	if((op-np) < 1.0f) //TODO: Pick a proper value through robust testing process!
            shotDetected = 1;
    }
  }

state(defendTheShot)
  {
    transition
    {
        if((theBallModel.estimate.position.angle() > 0.2) && (theBallModel.estimate.position.angle() < 3.14))
        goto dropRight;
	
        else if(theBallModel.estimate.position.angle() < 5.84)
        goto dropLeft;

	else
	goto defendCenter;
    }
    action
    {

    }
  }

state(defendCenter)
    {
      transition
      {
        if(state_time > 5000)
          goto start;
      }

      action
      {
       	// The robot spread legs if ball forward
    	SpecialAction(SpecialActionRequest::spreadLegs);
      }
    }

state(dropLeft)
  {
    transition
    {
        if(state_time > 5000)
          goto start;
    }

    action
    {
      // the robot fall left
    	SpecialAction(SpecialActionRequest::fallLeft);
    }
  }

state(dropRight)
  {
    transition
    {
        if(state_time > 5000)
          goto start;
    }

    action
    {
      // the robot fall right
    	SpecialAction(SpecialActionRequest::fallRight);
    }
  }

}
