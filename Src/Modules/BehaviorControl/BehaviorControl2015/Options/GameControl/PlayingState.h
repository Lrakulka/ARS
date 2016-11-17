option(PlayingState)
{
  initial_state(play)
  {
    
     transition
    {
    if(1)
        goto polobrot_1;
    }
    action
    { }
}
	
  state(polobrot_1)
{
transition
{if(state_time>6000) goto polobrot_2;}
action
{WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(3.142f, 0.f, 0.f));}
}


  state(polobrot_2)
{
transition
{if(state_time>6000) goto polobrot_3;}
action
{WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(3.143f, 0.f, 0.f));}
}

  state(polobrot_3)
{
transition
{if(state_time>6000) goto polobrot_4;}
action
{WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(3.144f, 0.f, 0.f));}
}

  state(polobrot_4)
{
transition
{if(state_time>6000) goto decision_state;}
action
{WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(3.145f, 0.f, 0.f));}
}
  


state(decision_state)
  {
  action
  {
WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
  Goalie();
  }

  }
}
