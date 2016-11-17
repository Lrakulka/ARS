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

    transition
    {
      if(libCodeRelease.timeSinceBallWasSeen() > 7000)
        goto lookAround;

      if(shotDetected)
        goto defendTheShot;
    }
    action
    {
        float op = theBallModel.estimate.position.norm();
        float np = op;

        
            op = np;
            np = theBallModel.estimate.position.norm();
        
	if((op-np) < 1.0f)
        shotDetected = 1;
    }
  }

state(defendTheShot)
  {
//TODO: REMOVE AND REWRITE
    transition
    {
        if(libCodeRelease.timeSinceBallWasSeen() < 300)
        goto trackTheBall;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
    }
  }

/* ODTAD

initial_state(start)
  {
    transition
    {
      if(state_time > 1000)
        goto detectShot;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      Stand();
    }
  }

  state(detectShot)
  {
    transition
    {*/
       /* if (shotDetected) {
          goto saveShot;
       }
       */
        /*if(libCodeRelease.timeSinceBallWasSeen() < 300)
        goto trackTheBall;
    }
    action
    {
      theHeadControlMode = HeadControl::lookLeftAndRight;
      // process frame
      // determine if the shot was shot
    }
  }

DOTAD MIELISMY
*/

/*
  state(trackTheBall)
  {
    transition
    {
      if(libCodeRelease.timeSinceBallWasSeen() > 7000)
        goto turnToBall;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      WalkAtSpeedPercentage(Pose2f(1.f, 0.f, 0.f));
    }
  }



  state(saveShot)
  {
    action
    {
      // lay down the goalie
      // if (direction == DIR_LEFT) {
     */ /*
        // walk to the left
        WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
         } else {
        // walk to the right
        WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
         }
*/ /*
    }
  }

  state(turnToBall)
  {
    transition
    {
      if(libCodeRelease.timeSinceBallWasSeen() > 7000)
        goto searchForBall;
      if(std::abs(theBallModel.estimate.position.angle()) < 5_deg)
        goto walkToBall;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      // WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
    }
  }
*/
  /* state(alignToGoal)
  {
    transition
    {
      if(libCodeRelease.timeSinceBallWasSeen() > 7000)
        goto searchForBall;
      if(std::abs(libCodeRelease.angleToGoal) < 10_deg && std::abs(theBallModel.estimate.position.y()) < 100.f)
        goto alignBehindBall;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(libCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 400.f, theBallModel.estimate.position.y()));
    }
  }

  state(alignBehindBall)
  {
    transition
    {
      if(libCodeRelease.timeSinceBallWasSeen() > 7000)
        goto searchForBall;
      if(libCodeRelease.between(theBallModel.estimate.position.y(), 20.f, 50.f)
          && libCodeRelease.between(theBallModel.estimate.position.x(), 140.f, 170.f)
          && std::abs(libCodeRelease.angleToGoal) < 2_deg)
        goto kick;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(libCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() - 30.f));
    }
  }

  state(kick)
  {
    transition
    {
      if(state_time > 3000 || (state_time > 10 && action_done))
        goto start;
    }
    action
    {
      Annotation("Alive and Kickin'");
      theHeadControlMode = HeadControl::lookForward;
      InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 160.f, theBallModel.estimate.position.y() - 55.f));
    }
  } */
}

