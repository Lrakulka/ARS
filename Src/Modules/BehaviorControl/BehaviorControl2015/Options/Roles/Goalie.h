/**
 * Goalie behaviour
 */
option(Goalie)
{
  // Initially, goalie stands still for a one second
  initial_state(start)
  {
    transition
    {
      if (state_time > 1000) // After one second
        goto lookAround; // Go to "looking around" state
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward; // stand stil with head straight
    }
  }

  // Goalie keeps rotating his head, in order to cover as much field space as possible
  state(lookAround)
  {
    transition
    {
        if (libCodeRelease.timeSinceBallWasSeen() < 300) // If a ball is lost from the sight
          goto trackTheBall; // Look for the ball
    }
    action
    {
      theHeadControlMode = HeadControl::lookLeftAndRight; // While in state, keep rotating robot's head
    }
  }

  // Goalie tries to detect the moment, when the shot is made by the striker
  state(trackTheBall)
  {
    transition
    {
      if (libCodeRelease.timeSinceBallWasSeen() > 7000) // If the ball is lost from the sight
        goto lookAround;  // Look for the ball

      if(theBallModel.estimate.position.norm() < 1100.f) // If the ball is close enough
	      goto defendTheShot; // It means, that the shot has been made and it should be defended

      // Optionally, it is possible to print to the terminal distance to the ball
      fprintf(stderr, "norm = %f\n", (float)theBallModel.estimate.position.norm());
    }
    action
    {
      ;
    }
  }

  // Goalie tries to defend the shot made by the striker
  state(defendTheShot)
  {
    transition
    {
      // Optionally, it is possible to print to the terminal angle to the ball
      fprintf(stderr, "Angle: %f\n", theBallModel.estimate.position.angle());

      // If the angle is high enough, it means that the goalie should drop left
      if (theBallModel.estimate.position.angle() >= 0.04) {
        fprintf(stderr, "Goalie decided to drop left\n");
        goto dropLeft;
      }
      // If the angle is low enough, it means that the goalie should drop right
      else if (theBallModel.estimate.position.angle() <= -0.04) {
        fprintf(stderr, "Goalie decided to drop right\n");
        goto dropRight;
      }
      // Else, the ball is coming to the center of the ball, so goalie should stay
      else {
        fprintf(stderr, "Goalie decided to stay at centre\n");
        goto defendCenter;
      }
    }
    action
    {
      ;
    }
  }

  // Goalie tries to defend at the center of the goal
  state(defendCenter)
  {
    transition
    {
      if (state_time > 5000) // After 5 seconds of defending at the center
        goto start; // Goalie should stand up
    }
    action
    {
     	// The robot spreads his legs to cover more area of the goal
    	SpecialAction(SpecialActionRequest::spreadLegsM);
    }
  }

  // Goalie tries to drop to his left
  state(dropLeft)
  {
    transition
    {
      if (state_time > 5000) // After 5 seconds of defending
        goto start; // Goalie should stand up
    }
    action
    {
      // The robot falls to his left
    	SpecialAction(SpecialActionRequest::fallLeftM);
    }
  }

  // Goalie tries to drop to his right
  state(dropRight)
  {
    transition
    {
      if (state_time > 5000) // After 5 seconds of defending
        goto start; // Goalie should stand up
    }
    action
    {
      // The robot falls to his right
    	SpecialAction(SpecialActionRequest::fallRightM);
    }
  }
}
