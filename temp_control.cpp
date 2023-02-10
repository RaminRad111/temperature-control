#include <iostream>
#include <gtest/gtest.h>

#define TEMPERATURE_MIN 18
#define TEMPERATURE_MAX 27

class RoomTemperature {
 public:
  RoomTemperature(int min, int max)
      : min_temp_(min), max_temp_(max) {}

  void SetCurrentTemperature(int temp) { current_temp_ = temp; }

  int GetCurrentTemperature() const { return current_temp_; }

  int GetMinTemperature() const { return min_temp_; }

  int GetMaxTemperature() const { return max_temp_; }

  void StartHeating() {
    if (current_temp_ < max_temp_) {
      current_temp_++;
      std::cout << "Heating... Current temperature: " << current_temp_ << std::endl;
    }
  }

  void StartCooling() {
    if (current_temp_ > min_temp_) {
      current_temp_--;
      std::cout << "Cooling... Current temperature: " << current_temp_ << std::endl;
    }
  }

 private:
  int min_temp_;
  int max_temp_;
  int current_temp_;
};

class HeatingSystemStub {
 public:
  void Start(RoomTemperature& room_temperature) {
    std::cout << "Starting heating..." << std::endl;
    while (room_temperature.GetCurrentTemperature() < room_temperature.GetMinTemperature())
      room_temperature.StartHeating();
  }
};

class CoolingSystemStub {
 public:
  void Start(RoomTemperature& room_temperature) {
    std::cout << "Starting cooling..." << std::endl;
    while (room_temperature.GetCurrentTemperature() > room_temperature.GetMaxTemperature())
      room_temperature.StartCooling();
  }
};

class RoomTemperatureControl {
 public:
  RoomTemperatureControl(RoomTemperature& room_temperature,
                         HeatingSystemStub& heating_system,
                         CoolingSystemStub& cooling_system)
      : room_temperature_(room_temperature),
        heating_system_(heating_system),
        cooling_system_(cooling_system) {}

  void AdjustTemperature() {
    if (room_temperature_.GetCurrentTemperature() < room_temperature_.GetMinTemperature()) {
      heating_system_.Start(room_temperature_);
    } else if (room_temperature_.GetCurrentTemperature() > room_temperature_.GetMaxTemperature()) {
      cooling_system_.Start(room_temperature_);
    }
  }

 private:
  RoomTemperature& room_temperature_;
  HeatingSystemStub& heating_system_;
  CoolingSystemStub& cooling_system_;
};

TEST(RoomTemperatureControlTest, HeatingStartsWhenTemperatureIsLow) {
  RoomTemperature room_temperature(TEMPERATURE_MIN, TEMPERATURE_MAX);
  HeatingSystemStub heating_system;
  CoolingSystemStub cooling_system;
  RoomTemperatureControl temperature_control(room_temperature, heating_system, cooling_system);

  room_temperature.SetCurrentTemperature(15);
  temperature_control.AdjustTemperature();

  EXPECT_EQ(TEMPERATURE_MIN, room_temperature.GetCurrentTemperature());
}

TEST(RoomTemperatureControlTest, CoolingStartsWhenTemperatureIsHigh) {
  RoomTemperature room_temperature(TEMPERATURE_MIN, TEMPERATURE_MAX);
  HeatingSystemStub heating_system;
  CoolingSystemStub cooling_system;
  RoomTemperatureControl temperature_control(room_temperature, heating_system, cooling_system);

  room_temperature.SetCurrentTemperature(32);
  temperature_control.AdjustTemperature();

  EXPECT_EQ(TEMPERATURE_MAX, room_temperature.GetCurrentTemperature());
}

TEST(RoomTemperatureControlTest, NoActionWhenTemperatureIsInRange) {
  RoomTemperature room_temperature(TEMPERATURE_MIN, TEMPERATURE_MAX);
  HeatingSystemStub heating_system;
  CoolingSystemStub cooling_system;
  RoomTemperatureControl temperature_control(room_temperature, heating_system, cooling_system);

  room_temperature.SetCurrentTemperature(23);
  temperature_control.AdjustTemperature();

  EXPECT_EQ(23, room_temperature.GetCurrentTemperature());
}
