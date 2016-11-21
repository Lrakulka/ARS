option(PlayingState)
{
  initial_state(play)
  {
    transition
    {
      if(state_time > 1000)
        goto decision_state;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      Stand();
    }
  }
      
  state(decision_state)
  {
  	  transition
	  {
	      if(libCodeRelease.timeSinceBallWasSeen() > 7000)
	        goto searchForBall;

              if(theBallModel.estimate.position.norm() < 1200.f) {
	          goto Striker;
	      } else {
	      	  goto Goalie;
	      }
	  }
      action
      {
	      
      }
  }

  state(Goalie)
  {
    transition
    {
    }
    action
    {
	Goalie();
    }
  }

  state(Striker)
  {
    transition
    {
    }
    action
    {
	Striker();
    }
  }
  
  state(searchForBall)
  {
    transition
    {
      if(libCodeRelease.timeSinceBallWasSeen() < 300)
        goto decision_state;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;    
      WalkAtSpeedPercentage(Pose2f(1.f, 0.f, 0.f));
    }
  }
  
  
}

