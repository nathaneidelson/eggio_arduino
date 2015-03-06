
#define PATTERN_SIZE 30
#define VIBRATION_DURATION 100

/* The time cycle of the pattern. */
int time = 0;
/* The time of the current vibration pattern. */
int vibration_timer = 0;

/* Index of the current vibration */
int curr_pos = 0;

/* True if the vibration motor is currently on. */
bool motor_on = false;

/* Scalars to make 1->10 scale work. */
int delay_scale = 1000;
int intensity_scale = 15;
int intensity_offset = 70;

/* Pattern of meditation. 
   Each pair (i, d) represents a vibration in the pattern with intensity i and delay d. 
   Delay d occurs after its corresponding vibration completes.
   Both i and d range on a scale from 1 to 10. */
int pattern[PATTERN_SIZE][2]  = 
{  
{9, .1}, 
{9, 3},

// Range of intensitys
{10, .5},
{9, .5},
{8, .5},
{7, .5},
{6, .5},
{5, .5},
{4, .5},
{3, .5},
{2, .5},
{1, .5},
{0, .5},

// Marks the start
{7, 3},
{7, 3},
{6, 4},
{6, 4},
{6, 5},
{5, 6},
{5, 6},
{5, 7},
{5, 7},
{5, 7},
{5, 7},

{3, 7},
{3, 7},
{3, 7},

// Marks the end
{7, 1}, 
{7, 1}
};

int intensity_for_position (int pos)
{
  return intensity_offset + pattern[pos][0] * intensity_scale;
}

int delay_for_position (int pos)
{
  return pattern[pos][1] * delay_scale;
}

void setup() 
{  
  Serial.begin(9600);
  pinMode(11, OUTPUT);
}

void loop()
{
  
  if (curr_pos >= PATTERN_SIZE)
    abort();
    
  bool did_switch_off = switch_motor_with_intensity(intensity_for_position(curr_pos));
  
  if (did_switch_off) {
    delay (delay_for_position(curr_pos));
    curr_pos++;
  }
  
  vibration_timer++;
  time++;
}

/* Returns true if the motor was switched off, so the delay wait can begin. */
bool switch_motor_with_intensity(int intensity) 
{
    Serial.print(vibration_timer % VIBRATION_DURATION);
    Serial.print("\n");
  if (vibration_timer % VIBRATION_DURATION == 0) {
      vibration_timer = 0;
      if (motor_on) {
        analogWrite (11, 0);
        motor_on = false;
        return true;
      } else {
        if (intensity > intensity_offset && intensity <= 250)
          analogWrite (11, intensity);
        motor_on = true;
        return false;
      }
  }
  
  return false;
}

