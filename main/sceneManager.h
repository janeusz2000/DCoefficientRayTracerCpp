#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "core/vec3.h"
#include "main/rayTracer.h"
#include "main/simulator.h"
#include "main/trackers.h"
#include "obj/generators.h"
#include "obj/objects.h"

#include <memory>
#include <string_view>
#include <vector>

// TODO: This constructor is too long, fix it ;-)
// Holds all needed information to perform simulation.
struct SimulationProperties {
  explicit SimulationProperties(
      const std::vector<float> &frequencies /*[Hz]*/,
      collectionRules::CollectEnergyInterface *energyCollectionRules,
      float sourcePower = 500 /*[W]*/, int numOfCollectors = 37,
      int numOfRaySquared = 15)
      : frequencies_(frequencies),
        energyCollectionRules_(energyCollectionRules),
        sourcePower_(sourcePower), numOfCollectors_(numOfCollectors),
        numOfRaySquared_(numOfRaySquared) {}

  const std::vector<float> &frequencies() const { return frequencies_; }
  collectionRules::CollectEnergyInterface *energyCollectionRules() {
    return energyCollectionRules_;
  }

  float sourcePower() const { return sourcePower_; }
  int numOfCollectors() const { return numOfCollectors_; }
  int numOfRaySquared() const { return numOfRaySquared_; }

  collectionRules::CollectEnergyInterface *collectionRules() {
    return energyCollectionRules_;
  }

private:
  std::vector<float> frequencies_;
  collectionRules::CollectEnergyInterface *energyCollectionRules_;
  float sourcePower_;
  int numOfCollectors_;
  int numOfRaySquared_;
};

// This class is creating all necessary objects for simulation.
class SceneManager {
public:
  using energies = std::vector<float>;
  using energiesPerFrequency = std::vector<energies>;

  explicit SceneManager(
      Model *model, const SimulationProperties &simulationProperties,
      trackers::PositionTrackerInterface *positionTracker,
      trackers::CollectorsTrackerInterface *collectorsTracker);

  energiesPerFrequency run();

private:
  Model *model_;
  SimulationProperties simulationProperties_;
  RayTracer raytracer_;
  trackers::PositionTrackerInterface *positionTracker_;
  trackers::CollectorsTrackerInterface *collectorsTracker_;

  std::unique_ptr<generators::RandomRayOffseter> offseter_;
  std::unique_ptr<Model> referenceModel_;
};

#endif
