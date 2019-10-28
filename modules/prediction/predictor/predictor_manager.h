/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 * @brief Use predictor manager to manage all predictors
 */

#pragma once

#include <map>
#include <memory>

#include "modules/prediction/container/obstacles/obstacles_container.h"
#include "modules/prediction/predictor/predictor.h"
#include "modules/prediction/proto/prediction_conf.pb.h"

/**
 * @namespace apollo::prediction
 * @brief apollo::prediction
 */
namespace apollo {
namespace prediction {

class PredictorManager {
 public:
  /**
   * @brief Destructor
   */
  virtual ~PredictorManager() = default;

  /**
   * @brief Initializer
   * @param Prediction config
   */
  void Init(const PredictionConf& config);

  /**
   * @brief Get predictor
   * @return Pointer to the predictor
   */
  Predictor* GetPredictor(const ObstacleConf::PredictorType& type);

  /**
   * @brief Execute the predictor generation
   */
  void Run();

  /**
   * @brief Predict a single obstacle
   * @param A pointer to the specific obstacle
   * @param A pointer to the obstacles container
   * @param A pointer to prediction_obstacle
   * @param A pointer to adc_trajectory_container
   */
  void PredictObstacle(Obstacle* obstacle,
                       ObstaclesContainer* obstacles_container,
                       PredictionObstacle* const prediction_obstacle,
                       ADCTrajectoryContainer* adc_trajectory_container);

  /**
   * @brief Get prediction obstacles
   * @return Prediction obstacles
   */
  const PredictionObstacles& prediction_obstacles();

 private:
  /**
   * @brief Register a predictor by type
   * @param Predictor type
   */
  void RegisterPredictor(const ObstacleConf::PredictorType& type);

  /**
   * @brief Create a predictor by type
   * @param Predictor type
   * @return A unique pointer to the predictor
   */
  std::unique_ptr<Predictor> CreatePredictor(
      const ObstacleConf::PredictorType& type);

  /**
   * @brief Register all predictors
   */
  void RegisterPredictors();

  void PredictObstacles(ObstaclesContainer* obstacles_container,
                        ADCTrajectoryContainer* adc_trajectory_container);

  void PredictObstaclesInParallel(
      ObstaclesContainer* obstacles_container,
      ADCTrajectoryContainer* adc_trajectory_container);

 private:
  std::map<ObstacleConf::PredictorType, std::unique_ptr<Predictor>> predictors_;

  ObstacleConf::PredictorType vehicle_on_lane_predictor_ =
      ObstacleConf::LANE_SEQUENCE_PREDICTOR;

  ObstacleConf::PredictorType vehicle_off_lane_predictor_ =
      ObstacleConf::FREE_MOVE_PREDICTOR;

  ObstacleConf::PredictorType vehicle_in_junction_predictor_ =
      ObstacleConf::LANE_SEQUENCE_PREDICTOR;

  ObstacleConf::PredictorType cyclist_on_lane_predictor_ =
      ObstacleConf::LANE_SEQUENCE_PREDICTOR;

  ObstacleConf::PredictorType cyclist_off_lane_predictor_ =
      ObstacleConf::FREE_MOVE_PREDICTOR;

  ObstacleConf::PredictorType pedestrian_predictor_ =
      ObstacleConf::REGIONAL_PREDICTOR;

  ObstacleConf::PredictorType default_on_lane_predictor_ =
      ObstacleConf::LANE_SEQUENCE_PREDICTOR;

  ObstacleConf::PredictorType default_off_lane_predictor_ =
      ObstacleConf::FREE_MOVE_PREDICTOR;

  PredictionObstacles prediction_obstacles_;

  DECLARE_SINGLETON(PredictorManager)
};

}  // namespace prediction
}  // namespace apollo
