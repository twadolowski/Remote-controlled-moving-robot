IF distance > 2m then set TRACKING flag to 0
ELSE
   INITIAL_DIST - remember the distance and set TRACKING flag to 1

IF TRACKING flag is set
  if current_distance - INITIAL_DISTANCE > 0
     GO BACKWARD
  ELSE
     GO FORWARD


