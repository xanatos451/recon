Throttle (Ch3) - Brightness
Pitch (Ch1) - Speed

PotA - Hue
PotB - Saturation

SwA - Color/Cylon Direction (Left / Right)
SwB - Middle-Out (Enable / Disable)
SwC - Animation Type (Color Wipe / Cylon / Solid)
SwD - Linear Blend (Enable / Disable)



Wheel Position Input
absolute position percentage of 255
output 255,255,255,255


Controls:
	SwA - 2 position
	SwB - 2 position
	SwC - 3 position
	SwD - 2 posiiion
	PotA - variable pot
	PotB - variable pot
	LeftStick 
		Up/Down variable
	RightStick

Animations:
	Larson
		Edit Color1 (lead)
			- show solid color
			Select Color Profile
				Cycle Profile Up/Down
			Edit Width (of color one)
			 - show still display
			Brightness (of color one)
		Edit Color2
			Select Color Profile
			 - show solid color
				Cycle Profile Up/Down
			Edit Width (of color two)
			 - show still display
			Brightness (of color two)
		Direction
			Left/Right
		MiddleOut
			Enable/Disable
		Select Settings Profile
			Edit Settings Profile
			Save Settings Profile
			Delete Settings Profile
	TheaterChase
		Select Settings Profile
			Edit Profile
				Direction
					Left/Right
				MiddleOut
					Enable/Disable
				Color1
					Width
					Brightness
				Color2
					Width
					Brightness
				Save Profile
			Add New Settings Profile
				(same as Edit Settings Profile)			
			Delete Settings Profile
	Rainbow
		Direction
			Left/Right
		MiddleOut
			Enable/Disable
	Gradient
		EditColors
			SelectColor
			EditColor
			DeleteColor
			EditBrightness
		MiddleOut
			Enable/Disable
		Direction
			Left/Right
		Width
	Flash
		Select Settings Profile
			Edit Settings Profile
			 - Flash yellow profile three times
				Add Color
					Select Color Profile
					Brightness
					Save
					 - Flash green once
				Delete Color
					- Flash green twice then change to previous color
					- If last color, flash red three times then blank
				Save Settings Profile		
				 - Blink three times then display animation
			Select Settings Profile
			 - Cycle up/down settings profiles
			Delete Settings Profile
		
	Custom
		
Modes:
	Display Animation
		Animation Profile Select
			Edit Animation Settings
				Save Animation Settings
				Reset Animation Settings to Default
		Animation Speed
		Begin Animation
		Pause/Unpause/Continue Animation
		Animation Off/Start
		Brightness
		
	Display Static
		Select Color Profile
			Edit Color Profile
				SaveColorProfile
		Reset Color Profiles to Default
		Enable Gradient
			Gradient Direction
			Select End Color Profile
			Select Brightness
				Start
				End
		
	Lock Settings
	

Actions:
	- ChangeColorProfile
		- BlinkColorProfile
		- SaveColorProfile
		- EditColorHSL
		- EditColorRGBW
		
	- SelectColorProfile
	



SwD (low) -> (high): Adjust Selected Color Profile by HSL
 - AdjustColorProfile()
  - SwC (1) w/ SwD (high) = Hue
   - VrA = Adjust Hue values
  - SwC (2) w/ SwD (high) = Saturation
   - VrA = Adjust Saturation values
  - SwC (3) w/ SwD (high) = Luminosity
   - VrA = Adjust Luminosity values

  - Right Stick (hold up for 3s): Save Color Profile (blink 3 times fast to confirm save)
   - SaveColorProfile()
  - Right Stick (tap left/right): Cycle Color Profile Selection (blink n times slowly for color profile number)
   - CycleColorProfile()
   - SelectColorProfile()
   
  

CycleColorProfile()
- SwD (low): Show Selected Color Profile (where applicable)
 - Right Stick (right): Cycle Up Color Profile Selected (blink n times for color profile number)
  - Increase currColorProfile index number (roll over to 0 if index count exceeded) 
  - ColorProfileBlink() 
 - Right Stick (left): Cycle Down Color Profile Selected (blink n times for color profile number) 
  - Decrease currColorProfile index number (roll over to index count if 0)
  - ColorProfileBlink() 

- ColorProfileBlink()
 
 - 

SelectColorProfile()
- 

Set Middle-Out Animation
- SwD (low)
- SwC (2)