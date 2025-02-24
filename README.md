# CustomArrowStep

The arrow platform from Hazy Maze Cave in Super Mario 64. It can be customized to have any amount of arrows facing any direction. 
The models were made by Alex SMG.

## obj_args

|obj_arg|Name|Type|Default|Description|
|-------|----|----|-------|-----------|
|obj_arg0|Speed|float|5.0f|The speed at which the platform moves at.|
|obj_arg1|Number of arrows|int|4|The amount of arrows that the platform should have. To determine what arrows should be placed on the platform, it uses the first n arrows (by default: Arrow_1, Arrow_2, Arrow_3 and Arrow_4).|

## Making a custom arrow platform

*A video guide is available [here](https://youtu.be/xs4kj9pUgXs?t=12m07s).*

By default, you are given a `CustomArrowStep.arc` file. This will be the base of all your custom platforms.

1. Clone the file and give it a new name.
2. Export the `CustomArrowStep.bdl` file inside. Now you have two options:

**Using Blender + SuperBMD:**

2.1. Import the `.bdl` file into Blender by converting it using SuperBMD first.

2.2. You should see five bones, one of which being called `root` and the others being called `Arrow_1`, `Arrow_2`, `Arrow_3` and `Arrow_4` respectively. Simply move them around to your desire. If they should point in a different direction, make sure to also rotate them vertically (Z-Axis in Blender).

2.3. If you want to add any additional bones, you can do so too. Simply make sure that they are child bones of `root` and following the same naming scheme as the other bones (Anything below `Arrow_1` is ignored!).

2.4. Reimport the model as a `.bdl` file with SuperBMD. Make sure to name it after the `.arc` file (The `.kcl` and `.pa` need to stay untouched!).

**Using RiiStudio:**

2.1. Open the `.bdl` file with RiiStudio and click on the bone you want to change.

2.2. Head over to the Transformations tab on the right and adjust the Offset and Rotation values to your liking.

2.3. Save the model and reimport it into the `.arc` file. Make sure to name it after the `.arc` file (The `.kcl` and `.pa` need to stay untouched!).

*Note:* As of right now, there does not seem to be a way to create new child bones in RiiStudio, so to add new arrows, you need to use the Blender + SuperBMD method.

3. Once you did this, open the ProductMapObjDataTable and add your new platform with the class name `CustomArrowStep`. And you're done!