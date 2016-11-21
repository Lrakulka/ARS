option(PlayingState)
{
  initial_state(play)
  {
    transition
    {
    	if (theRobotInfo.number != 1) {
    		 Striker();
	      } else {
	      	   Goalie();
	      }
    }
  }  
}