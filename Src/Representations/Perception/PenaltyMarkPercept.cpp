/**
 * @file PenaltyMarkPercept.cpp
 * Implementation of a struct that represents a penalty mark.
 * @author Maik Schünemann
 */

#include "PenaltyMarkPercept.h"
#include "Representations/Infrastructure/FrameInfo.h"
#include "Tools/Debugging/DebugDrawings.h"
#include "Tools/Module/Blackboard.h"

void PenaltyMarkPercept::draw() const
{
  DECLARE_DEBUG_DRAWING("representation:PenaltyMarkPercept:Image", "drawingOnImage");
  DECLARE_DEBUG_DRAWING("representation:PenaltyMarkPercept:Field", "drawingOnField");

  if(Blackboard::getInstance().exists("FrameInfo"))
  {
    const FrameInfo& frameInfo = static_cast<const FrameInfo&>(Blackboard::getInstance()["FrameInfo"]);
    if(timeLastSeen == frameInfo.time)
    {
      CROSS("representation:PenaltyMarkPercept:Image", position.x(), position.y(), 5, 5, Drawings::solidPen, ColorRGBA::blue);
      CROSS("representation:PenaltyMarkPercept:Field", positionOnField.x(), positionOnField.y(), 40, 40, Drawings::solidPen, ColorRGBA::blue);
    }
  }
}
