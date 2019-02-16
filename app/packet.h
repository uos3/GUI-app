#pragma once

#include <QString>
#include "buffer.h"
#include <cstring>
#include <algorithm>

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

// Types of downlink packets, and functions to make them from loaded buffers.

// special functions (and macros) that let us serialize c arrays to json arrays,
// and c char arrays to json strings.
template <int S>
std::string nvp_string (char(&a)[S]) {
	return std::string(a, S - 1);
}
template <class T, int S>
std::vector<T> nvp_array (T(&a)[S]) {
	return std::vector<T>(a, a+S);
}
#define STRING_NVP(_s_STRING_NVP) cereal::make_nvp(#_s_STRING_NVP, nvp_string(_s_STRING_NVP))
#define ARRAY_NVP(_a_ARRAY_NVP) cereal::make_nvp(#_a_ARRAY_NVP, nvp_array(_a_ARRAY_NVP))


struct Status {
	char spacecraft_id[3];
	uint32_t time;
	bool time_source;
	char sequence_id[3];
	int8_t obc_temperature;
	int8_t battery_temperature;
	int8_t battery_voltage;
	uint8_t battery_current;
	uint8_t charge_current;
	bool antenna_deployment;
	uint16_t data_pending;
	uint8_t reboot_count;
	bool rails_status[6];
	int8_t rx_temperature;
	int8_t tx_temperature;
	int8_t pa_temperature;
	uint8_t rx_noisefloor;

	template <class Archive>
	void serialize (Archive& ar) {
		ar(STRING_NVP(spacecraft_id), CEREAL_NVP(time),
		   CEREAL_NVP(time_source), STRING_NVP(sequence_id),
		   CEREAL_NVP(obc_temperature), CEREAL_NVP(battery_temperature),
		   CEREAL_NVP(battery_voltage),  CEREAL_NVP(battery_current),
		   CEREAL_NVP(charge_current), CEREAL_NVP(antenna_deployment),
		   CEREAL_NVP(data_pending),  CEREAL_NVP(reboot_count),
		   ARRAY_NVP(rails_status), CEREAL_NVP(rx_temperature),
		   CEREAL_NVP(tx_temperature),  CEREAL_NVP(pa_temperature),
		   CEREAL_NVP(rx_noisefloor));
	}
};

struct GPS {
	char sequence_id[3];
	uint32_t timestamp;
	float lat;
	float lon;
	float alt;
	uint8_t hdop;
	uint8_t vdop;
	uint8_t pdop;
	uint8_t tdop;

	template <class Archive>
	void serialize (Archive& ar) {
		ar(STRING_NVP(sequence_id), CEREAL_NVP(timestamp), CEREAL_NVP(lat),
		   CEREAL_NVP(lon), CEREAL_NVP(alt), CEREAL_NVP(hdop), CEREAL_NVP(vdop),
		   CEREAL_NVP(pdop), CEREAL_NVP(tdop));
	}
};

struct IMU {
	char sequence_id[3];
	uint32_t timestamp;
	int16_t mag_x[5];
	int16_t mag_y[5];
	int16_t mag_z[5];
	int16_t gyro_x[5];
	int16_t gyro_y[5];
	int16_t gyro_z[5];
	int16_t accel_x[5];
	int16_t accel_y[5];
	int16_t accel_z[5];

	template <class Archive>
	void serialize (Archive& ar) {
		ar(STRING_NVP(sequence_id), CEREAL_NVP(timestamp), ARRAY_NVP(mag_x),
		   ARRAY_NVP(mag_y), ARRAY_NVP(mag_z), ARRAY_NVP(gyro_x),
		   ARRAY_NVP(gyro_y), ARRAY_NVP(gyro_z), ARRAY_NVP(accel_x),
		   ARRAY_NVP(accel_y), ARRAY_NVP(accel_z));
	}
};

struct Health {
	char sequence_id[3];
	uint32_t timestamp;
	int8_t obc_temperature;
	int8_t rx_temperature;
	int8_t tx_temperature;
	int8_t pa_temperature;
	uint8_t reboot_count;
	uint16_t data_packets_pending;
	bool antenna_switch;
	uint8_t rx_noisefloor;
	uint8_t detected_flash_errors;
	uint8_t detected_ram_errors;
	int16_t battery_voltage;
	uint16_t battery_current;
	int16_t battery_temperature;
	uint16_t charge_current;
	int16_t mppt_voltage;
	uint16_t solar_n1_current;
	uint16_t solar_n2_current;
	uint16_t solar_e1_current;
	uint16_t solar_e2_current;
	uint16_t solar_s1_current;
	uint16_t solar_s2_current;
	uint16_t solar_w1_current;
	uint16_t solar_w2_current;
	uint16_t solar_t1_current;
	uint16_t solar_t2_current;
	bool rails_switch_status[6];
	bool rails_overcurrent_status[6];
	uint16_t rail_1_boot_count;
	uint16_t rail_1_overcurrent_count;
	int16_t rail_1_voltage;
	uint16_t rail_1_current;
	uint16_t rail_2_boot_count;
	uint16_t rail_2_overcurrent_count;
	int16_t rail_2_voltage;
	uint16_t rail_2_current;
	uint16_t rail_3_boot_count;
	uint16_t rail_3_overcurrent_count;
	int16_t rail_3_voltage;
	uint16_t rail_3_current;
	uint16_t rail_4_boot_count;
	uint16_t rail_4_overcurrent_count;
	int16_t rail_4_voltage;
	uint16_t rail_4_current;
	uint16_t rail_5_boot_count;
	uint16_t rail_5_overcurrent_count;
	int16_t rail_5_voltage;
	uint16_t rail_5_current;
	uint16_t rail_6_boot_count;
	uint16_t rail_6_overcurrent_count;
	int16_t rail_6_voltage;
	uint16_t rail_6_current;
	int16_t _3v3_voltage;
	uint16_t _3v3_current;
	int16_t _5v_voltage;
	uint16_t _5v_current;

	template <class Archive>
	void serialize (Archive& ar) {
		ar(STRING_NVP(sequence_id), CEREAL_NVP(timestamp),
		   CEREAL_NVP(obc_temperature), CEREAL_NVP(rx_temperature),
		   CEREAL_NVP(tx_temperature),  CEREAL_NVP(pa_temperature),
		   CEREAL_NVP(reboot_count), CEREAL_NVP(data_packets_pending),
		   CEREAL_NVP(antenna_switch),  CEREAL_NVP(rx_noisefloor),
		   CEREAL_NVP(detected_flash_errors),  CEREAL_NVP(detected_ram_errors),
		   CEREAL_NVP(battery_voltage), CEREAL_NVP(battery_current),
		   CEREAL_NVP(battery_temperature),  CEREAL_NVP(charge_current),
		   CEREAL_NVP(mppt_voltage), CEREAL_NVP(solar_n1_current),
		   CEREAL_NVP(solar_n2_current),  CEREAL_NVP(solar_e1_current),
		   CEREAL_NVP(solar_e2_current), CEREAL_NVP(solar_s1_current),
		   CEREAL_NVP(solar_s2_current),  CEREAL_NVP(solar_w1_current),
		   CEREAL_NVP(solar_w2_current), CEREAL_NVP(solar_t1_current),
		   CEREAL_NVP(solar_t2_current),  ARRAY_NVP(rails_switch_status),
		   ARRAY_NVP(rails_overcurrent_status),  CEREAL_NVP(rail_1_boot_count),
		   CEREAL_NVP(rail_1_overcurrent_count), CEREAL_NVP(rail_1_voltage),
		   CEREAL_NVP(rail_1_current),  CEREAL_NVP(rail_2_boot_count),
		   CEREAL_NVP(rail_2_overcurrent_count),  CEREAL_NVP(rail_2_voltage),
		   CEREAL_NVP(rail_2_current), CEREAL_NVP(rail_3_boot_count),
		   CEREAL_NVP(rail_3_overcurrent_count),  CEREAL_NVP(rail_3_voltage),
		   CEREAL_NVP(rail_3_current),  CEREAL_NVP(rail_4_boot_count),
		   CEREAL_NVP(rail_4_overcurrent_count), CEREAL_NVP(rail_4_voltage),
		   CEREAL_NVP(rail_4_current),  CEREAL_NVP(rail_5_boot_count),
		   CEREAL_NVP(rail_5_overcurrent_count),  CEREAL_NVP(rail_5_voltage),
		   CEREAL_NVP(rail_5_current), CEREAL_NVP(rail_6_boot_count),
		   CEREAL_NVP(rail_6_overcurrent_count),  CEREAL_NVP(rail_6_voltage),
		   CEREAL_NVP(rail_6_current),  CEREAL_NVP(_3v3_voltage),
		   CEREAL_NVP(_3v3_current),  CEREAL_NVP(_5v_voltage),
		   CEREAL_NVP(_5v_current));
	}
};

struct Img {
	char sequence_id[3];
	uint32_t timestamp;
	uint8_t image_id;
	uint16_t fragment_id;
	uint16_t num_fragments;
	char image_data[76];

	template <class Archive>
	void serialize (Archive& ar) {
		ar(STRING_NVP(sequence_id), CEREAL_NVP(timestamp),
		   CEREAL_NVP(image_id), CEREAL_NVP(fragment_id),
		   CEREAL_NVP(num_fragments), STRING_NVP(image_data));
	}
};

struct Config {
	char sequence_id[3];
	uint32_t timestamp;

	// TODO #finish

	template <class Archive>
	void serialize (Archive& ar) {
		ar(STRING_NVP(sequence_id), CEREAL_NVP(timestamp));
	}
};

union Payload {
	GPS gps;
	IMU imu;
	Health health;
	Img img;
	Config config;
};

enum class PayloadType { Morse=1, GPS=2, IMU=3, Health=4, Img=5, Config=6 };

struct Packet {
	char crc[3];
	char hash[17];
	PayloadType type;
	Status status;
	Payload payload;
	uint32_t downlink_time;

	template <class Archive>
	void serialize (Archive& ar) {
		switch (type) {
			case PayloadType::GPS:
				ar(STRING_NVP(crc), STRING_NVP(hash), CEREAL_NVP(type),
				   CEREAL_NVP(status), CEREAL_NVP(payload.gps),
				   CEREAL_NVP(downlink_time));
				break;
			case PayloadType::IMU:
				ar(STRING_NVP(crc), STRING_NVP(hash), CEREAL_NVP(type),
				   CEREAL_NVP(status), CEREAL_NVP(payload.imu),
				   CEREAL_NVP(downlink_time));
				break;
			case PayloadType::Health:
				ar(STRING_NVP(crc), STRING_NVP(hash), CEREAL_NVP(type),
				   CEREAL_NVP(status), CEREAL_NVP(payload.health),
				   CEREAL_NVP(downlink_time));
				break;
			case PayloadType::Img:
				ar(STRING_NVP(crc), STRING_NVP(hash), CEREAL_NVP(type),
				   CEREAL_NVP(status), CEREAL_NVP(payload.img),
				   CEREAL_NVP(downlink_time));
				break;
			case PayloadType::Config:
				ar(STRING_NVP(crc), STRING_NVP(hash), CEREAL_NVP(type),
				   CEREAL_NVP(status), CEREAL_NVP(payload.config),
				   CEREAL_NVP(downlink_time));
				break;
			default:
				std::string msg = "invalid payload type \"";
				msg += std::to_string(static_cast<int>(type));
				msg += "\" while parsing packet.";
				throw std::runtime_error(msg);
				break;
		}
	}
};


/// \brief Parses a raw binary packet into a Packet struct, containing the
///        appropriate payload.
void from_buffer (GPS& g, Buffer& b);
void from_buffer (IMU& i, Buffer& b);
void from_buffer (Img& i, Buffer& b);
void from_buffer (Health& h, Buffer& b);
void from_buffer (Status& s, Buffer& b);
void from_buffer (Packet& p, Buffer& b);
void from_buffer (Packet& p, Buffer& b, uint32_t downlink_time);
