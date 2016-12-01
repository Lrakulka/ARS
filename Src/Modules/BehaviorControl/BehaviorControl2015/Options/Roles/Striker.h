/**
 * Striker behaviour
 */
option(Striker)
{
  // Initially, goalie stands still for a one second
  initial_state(start)
  {
    transition
    {
      if (state_time > 1000) // After one second
        goto turnToBall; // Striker turns to the ball
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward; // Keeps his head straight
      Stand(); // Stands up
    }
  }

  // Striker turns to the ball's direction
  state(turnToBall)
  {
    transition
    {
      if (libCodeRelease.timeSinceBallWasSeen() > 7000) // If the ball hasn't been seen for too long
        goto searchForBall; // Robot looks for the ball
      if (std::abs(theBallModel.estimate.position.angle()) < 5_deg) // If the ball is in front of the robot
        goto walkToBall; // Striker can walk to the ball
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward; // Robot keeps his head looking forward
      WalkToTarget( Pose2f(50.f, 50.f, 50.f)  // Robot rotates to the ball's position
                  , Pose2f(theBallModel.estimate.position.angle()
                  , 0.f, 0.f));
    }
  }

  // Striker walks to the ball's position
  state(walkToBall)
  {
    transition
    {
      if (libCodeRelease.timeSinceBallWasSeen() > 7000) // If the ball hasn't been seen for too long
        goto searchForBall; // Robot starts looking for the ball again
      if (theBallModel.estimate.position.norm() < 500.f) // If the ball is close enough to the striker
        goto alignToGoal; // Align to the goal
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward; // Robot keeps his head looking forward
      WalkToTarget( Pose2f(50.f, 50.f, 50.f) // Robot walks to the ball's position
                  , theBallModel.estimate.position);
    }
  }

  // Striker aligns to the goal
  state(alignToGoal)
  {
    transition
    {
      if (libCodeRelease.timeSinceBallWasSeen() > 7000) // If the ball hasn't been seen for too long
        goto searchForBall; // Robot starts looking for the ball again
      if (std::abs(libCodeRelease.angleToGoal) < 10_deg && std::abs(theBallModel.estimate.position.y()) < 100.f) {
        // If the angle to goal is low enough, and ball is close enough, it's time to align to the ball
	        if (rand() % 2) // Choose randomly, which foot to align to
	          goto alignBehindBallRight; // Align for kicking with right foot
	        goto alignBehindBallLeft; // Align for kicking with left foot
	    }
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;  // Robot keeps his head looking forward
      WalkToTarget( Pose2f(100.f, 100.f, 100.f) // Robot walks close to the ball
                  , Pose2f( libCodeRelease.angleToGoal
                          , theBallModel.estimate.position.x() - 400.f
                          , theBallModel.estimate.position.y()
                          )
                  );
    }
  }

  // Striker aligns to the ball, so that he will be able to kick with his left foot
  state(alignBehindBallLeft)
  {
    transition
    {
      if (libCodeRelease.timeSinceBallWasSeen() > 7000) // If the ball hasn't been seen for too long
        goto searchForBall; // Robot starts looking for the ball again
      if (libCodeRelease.between(theBallModel.estimate.position.y(), 20.f, 50.f)
          && libCodeRelease.between(theBallModel.estimate.position.x(), 140.f, 170.f)
          && std::abs(libCodeRelease.angleToGoal) < 2_deg) { // If the ball position is appropriate
		        goto left_kick; // Striker can kick the ball with his left foot
	    }
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward; // Robot keeps his head looking forward
      WalkToTarget( Pose2f(80.f, 80.f, 80.f) // Robot walks to the ball
                  , Pose2f( libCodeRelease.angleToGoal
                          , theBallModel.estimate.position.x() - 150.f // Note the offset for the left foot
                          , theBallModel.estimate.position.y() - 30.f  // Note the offset for the left foot
                          )
                  );
    }
  }

  // Striker aligns to the ball, so that he will be able to kick with his right foot
  state(alignBehindBallRight)
  {
    transition
    {
      // To output some debug information, uncomment the following lines:
      // fprintf(stderr
      //        , "px = %f  py = %f\n"
      //        , (float)theBallModel.estimate.position.x()
      //        , (float)theBallModel.estimate.position.y()
      // );

      if (libCodeRelease.timeSinceBallWasSeen() > 7000) // If the ball hasn't been seen for too long
        goto searchForBall; // Robot starts looking for the ball again
      if(libCodeRelease.between(theBallModel.estimate.position.y(), -50.f, -20.f)
          && libCodeRelease.between(theBallModel.estimate.position.x(), 140.f, 170.f)
          && std::abs(libCodeRelease.angleToGoal) < 2_deg) { // If the ball position is appropriate
		        goto right_kick; // Striker can kick the ball with his right foot
	    }
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward; // Robot keeps his head looking forward
      WalkToTarget( Pose2f(80.f, 80.f, 80.f) // Robot walks to the ball
                  , Pose2f( libCodeRelease.angleToGoal
                          , theBallModel.estimate.position.x() - 150.f // Note the offset for the right foot
                          , theBallModel.estimate.position.y() + 40.f  // Note the offset for the right foot
                          )
                  );
    }
  }

  // Striker kicks the ball with his right foot
  state(right_kick)
  {
    transition
    {
      if (state_time > 3000 || (state_time > 10 && action_done)) // If the action was performed
        goto start; // Robot goes through all the procedues for detecting the ball, walking in and shooting again
    }
    action
    {
      Annotation("Alive and Kickin'");
      theHeadControlMode = HeadControl::lookForward; // Robot keeps his head looking forward
      InWalkKick( WalkRequest::right // Robot kicks the ball with his right foot
                , Pose2f( libCodeRelease.angleToGoal
                        , theBallModel.estimate.position.x() - 160.f
                        , theBallModel.estimate.position.y() - 55.f
                        )
                );
    }
  }

  // Striker kicks the ball with his left foot
  state(left_kick)
  {
    transition
    {
      if (state_time > 3000 || (state_time > 10 && action_done)) // If the action was performed
        goto start; // Robot goes through all the procedues for detecting the ball, walking in and shooting again
    }
    action
    {
      Annotation("Alive and Kickin'");
      theHeadControlMode = HeadControl::lookForward; // Robot keeps his head looking forward
      InWalkKick( WalkRequest::right // Robot kicks the ball with his left foot
                , Pose2f( libCodeRelease.angleToGoal
                        , theBallModel.estimate.position.x() + 160.f
                        , theBallModel.estimate.position.y() - 55.f
                        )
                );
    }
  }

  // Striker looks for the ball
  state(searchForBall)
  {
    transition
    {
      if (libCodeRelease.timeSinceBallWasSeen() < 300) // Shortly after losing the ball out of sight
        goto turnToBall; // Begin turning to the ball
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward; // Robot keeps his head looking forward
      WalkAtSpeedPercentage(Pose2f(1.f, 0.f, 0.f));
    }
  }
}
