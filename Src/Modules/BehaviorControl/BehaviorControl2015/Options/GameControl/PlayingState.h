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
  
  
  state(half_turn_1)
  {
      transition
      {
          if (state_time > 6000)
             goto half_turn_2;
      }
      action
      {
    	  SpecialAction(SpecialActionRequest::testAnimation);
          //WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(3.142f, 0.f, 0.f));
      }
  }


  state(half_turn_2)
  {
      transition
      {
           if (state_time > 6000)
               goto half_turn_3;
      }
      action
      {
          WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(3.143f, 0.f, 0.f));
      }
  }

  state(half_turn_3)
  {
      transition
      {
           if (state_time > 6000)
               goto half_turn_4;
      }
      action
      {
           WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(3.144f, 0.f, 0.f));
      }
  }

  state(half_turn_4)
  {
      transition
      {
           if (state_time > 6000)
               goto decision_state;
      }
      action
      {
           WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(3.145f, 0.f, 0.f));
      }
  }
  
}

