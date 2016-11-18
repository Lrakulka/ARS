option(PlayingState)
{
  initial_state(play)
  {
      transition
      {
          // Do 4 half turn's to allow the robot to detect surroundings
          // At the end of half_turn_4 the robot goes to detection phase
          // And chooses the appropriate role- striker or goalie (TODO!)
          goto half_turn_1;
      }
      action
      {
          ;
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
          WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(3.142f, 0.f, 0.f));
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

  state(decision_state)
  {
      int predicate = 0;
      action
      {
          WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));

          predicate = 0; // TODO: Check distance to the goal

          if (predicate) {
              Goalie();
          } else {
              Striker();
          }
      }
  }
}
