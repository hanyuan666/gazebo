/*
 * Copyright (C) 2015 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include "gazebo/test/ServerFixture.hh"
#include "test/util.hh"
#include "gazebo/physics/PhysicsTypes.hh"
#include "gazebo/physics/Model.hh"

using namespace gazebo;

class ModelTest : public ServerFixture { };

//////////////////////////////////////////////////
TEST_F(ModelTest, Scale)
{
  // Load a world
  this->Load("worlds/empty.world", true);
  auto world = physics::get_world("default");

  // Create a base to be the model's parent
  physics::BasePtr basePtr;
  basePtr.reset(new physics::Base(physics::BasePtr()));
  basePtr->SetName("world_root_element");
  basePtr->SetWorld(world);

  // Create the model
  physics::ModelPtr modelPtr(new physics::Model(basePtr));
  EXPECT_TRUE(modelPtr != NULL);

  // Check default scale
  EXPECT_EQ(modelPtr->Scale(), ignition::math::Vector3d(1, 1, 1));

  // Set scale
  ignition::math::Vector3d scale(0.5, 2, 3);
  modelPtr->SetScale(scale);

  // Check scale
  EXPECT_EQ(modelPtr->Scale(), scale);

  // Cleanup
  modelPtr.reset();
}

//////////////////////////////////////////////////
TEST_F(ModelTest, NestedModelSensorScopedName)
{
  this->Load("test/worlds/deeply_nested_models.world", true);

  auto world = physics::get_world("default");
  ASSERT_TRUE(world != nullptr);

  auto model = world->GetModel("model_03");
  ASSERT_TRUE(model != nullptr);

  gzmsg << "Get a scoped sensor name" << std::endl;

  const std::vector<std::string> imuScopedName =
      model->SensorScopedName("imu_sensor");
  ASSERT_EQ(imuScopedName.size(), static_cast<unsigned int>(1));
  EXPECT_EQ(imuScopedName[0],
    "default::model_00::model_01::model_02::model_03::imu_link::imu_sensor");

  gzmsg << "Get a inexisting scoped sensor name" << std::endl;

  const std::vector<std::string> noScopedName =
      model->SensorScopedName("no_sensor");
  ASSERT_EQ(noScopedName.size(), static_cast<unsigned int>(0));
}

//////////////////////////////////////////////////
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
