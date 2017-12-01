///list of existing bugs:
/*
- game crushes when three (or more?) enemies are killed in a row (within a second or so) - SEEMS TO BE FIXED, THE
  PROBLEM WAS IN USING DELETE ON OBJECTS CREATED WITHOUT NEW (e.g., Enemy e(); delete(&e);)
- make hero sprite (and other sprites?) transparent, so it does'n look like white square when going through
  dark map squares (e.g. when it's falling as in dead animation)
- make the first slide of move animations active (not just standing), because now it takes
  some time to play animation since the fist slide is the one where character is standing
- Suppose the character stands to the right of the block with trapped enemy. Hold left button and
  press up button to jump. Instead of jumping character will teleport to the left of the block. Seems like
  collision detection and reaction of the character in case of fire works incorrectly
- hero cannot jump into tunnel of height == hero.height, make hero's tile height smaller than map tile height?
