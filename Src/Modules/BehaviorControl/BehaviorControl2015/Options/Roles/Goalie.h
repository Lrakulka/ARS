/** A test goalie option without common decision */
option(Goalie)
{

initial_state(start)
  {
    transition
    {
      if(state_time > 3000)
        goto lookAround;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(0.f, 400.f, 0.f));
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

      if(theBallModel.estimate.position.norm() < 900.f)
	goto defendTheShot;
    }
    action
    {
      /*op = np;
      np = theBallModel.estimate.position.norm();

    	if((op-np) < 1.0f) //TODO: Pick a proper value through robust testing process!
            shotDetected = 1;
    */
    }
  }

state(defendTheShot)
  {
    transition
    {
        if((theBallModel.estimate.position.angle() >= 0.1) && (theBallModel.estimate.position.angle() < 3.14))
        goto dropLeft;

        if((theBallModel.estimate.position.angle() <= 6.08) && (theBallModel.estimate.position.angle() > 3.14))
        goto dropRight;

        if((theBallModel.estimate.position.angle() < 0.1) || (theBallModel.estimate.position.angle() > 6.08))
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
