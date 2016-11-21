option(PlayingState)
{
  initial_state(play)
  {
    
    action
    {
    	if (theRobotInfo.number != 1) {
    		 Striker();
	      } else {
	      	   Goalie();
	      }
    }
  }  
}

