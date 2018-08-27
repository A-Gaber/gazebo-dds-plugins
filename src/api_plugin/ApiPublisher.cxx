/*
 * Copyright 2018 Real-Time Innovations, Inc.
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
 */

#include <unordered_map>

#include <dds/core/ddscore.hpp>
#include <dds/domain/find.hpp>
#include <dds/pub/ddspub.hpp>
#include <rti/request/rtirequest.hpp>

#include "common/CommandLineParser.hpp"
#include "common/DdsUtils.hpp"

#include "gazebo_msgs/srv/Default_Response.hpp"
#include "gazebo_msgs/srv/DeleteLight_Request.hpp"
#include "gazebo_msgs/srv/DeleteModel_Request.hpp"
#include "gazebo_msgs/srv/GetJointProperties_Request.hpp"
#include "gazebo_msgs/srv/GetJointProperties_Response.hpp"
#include "gazebo_msgs/srv/GetLightProperties_Request.hpp"
#include "gazebo_msgs/srv/GetLightProperties_Response.hpp"
#include "gazebo_msgs/srv/GetLinkProperties_Request.hpp"
#include "gazebo_msgs/srv/GetLinkProperties_Response.hpp"
#include "gazebo_msgs/srv/GetLinkState_Request.hpp"
#include "gazebo_msgs/srv/GetLinkState_Response.hpp"
#include "gazebo_msgs/srv/GetModelProperties_Request.hpp"
#include "gazebo_msgs/srv/GetModelProperties_Response.hpp"
#include "gazebo_msgs/srv/GetModelState_Request.hpp"
#include "gazebo_msgs/srv/GetModelState_Response.hpp"
#include "gazebo_msgs/srv/GetWorldProperties_Response.hpp"
#include "gazebo_msgs/srv/SetLightProperties_Request.hpp"
#include "gazebo_msgs/srv/SetLinkProperties_Request.hpp"
#include "gazebo_msgs/srv/SetModelState_Request.hpp"
#include "gazebo_msgs/srv/SetLinkState_Request.hpp"
#include "std_msgs/msg/Empty.hpp"

template <typename T, typename T2>
T2 send_request(
        const dds::domain::DomainParticipant &participant,
        const std::string &service_name,
        T &request)
{
    rti::request::Requester<T, T2> requester(::dds::core::null);

    // Create requester
    gazebo::dds::utils::create_requester<T, T2>(
            requester,
            participant,
            service_name,
            ::dds::core::QosProvider::Default());

    // Call the service
    T2 reply = gazebo::dds::utils::call_service<T, T2>(requester, request);

    return reply;
}

void delete_model(
        const dds::domain::DomainParticipant &participant,
        const std::string &service_name,
        std::unordered_map<std::string, std::vector<std::string>> model_name)
{
    gazebo_msgs::srv::DeleteModel_Request request(model_name["model_name"][0]);

    gazebo_msgs::srv::Default_Response reply = send_request<
            gazebo_msgs::srv::DeleteModel_Request,
            gazebo_msgs::srv::Default_Response>(
            participant, service_name, request);

    std::cout << reply.status_message() << std::endl;
}

void delete_light(
        const dds::domain::DomainParticipant &participant,
        std::string service_name,
        std::unordered_map<std::string, std::vector<std::string>> light_name)
{
    gazebo_msgs::srv::DeleteLight_Request request(light_name["light_name"][0]);

    gazebo_msgs::srv::Default_Response reply = send_request<
            gazebo_msgs::srv::DeleteLight_Request,
            gazebo_msgs::srv::Default_Response>(
            participant, service_name, request);

    std::cout << reply.status_message() << std::endl;
}

void get_light_properties(
        const dds::domain::DomainParticipant &participant,
        std::string service_name,
        std::unordered_map<std::string, std::vector<std::string>>
                light_properties)
{
    gazebo_msgs::srv::GetLightProperties_Request request(
            light_properties["light_name"][0]);

    gazebo_msgs::srv::GetLightProperties_Response reply = send_request<
            gazebo_msgs::srv::GetLightProperties_Request,
            gazebo_msgs::srv::GetLightProperties_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

void get_world_properties(
        const dds::domain::DomainParticipant &participant,
        std::string service_name)
{
    std_msgs::msg::Empty request;

    gazebo_msgs::srv::GetWorldProperties_Response reply = send_request<
            std_msgs::msg::Empty,
            gazebo_msgs::srv::GetWorldProperties_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

void get_joint_properties(
        const dds::domain::DomainParticipant &participant,
        std::string service_name,
        std::unordered_map<std::string, std::vector<std::string>>
                joint_properties)
{
    gazebo_msgs::srv::GetJointProperties_Request request(
            joint_properties["joint_name"][0]);

    gazebo_msgs::srv::GetJointProperties_Response reply = send_request<
            gazebo_msgs::srv::GetJointProperties_Request,
            gazebo_msgs::srv::GetJointProperties_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

void get_link_properties(
        const dds::domain::DomainParticipant &participant,
        std::string service_name,
        std::unordered_map<std::string, std::vector<std::string>>
                link_properties)
{
    gazebo_msgs::srv::GetLinkProperties_Request request(
            link_properties["link_name"][0]);

    gazebo_msgs::srv::GetLinkProperties_Response reply = send_request<
            gazebo_msgs::srv::GetLinkProperties_Request,
            gazebo_msgs::srv::GetLinkProperties_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

void get_link_state(
        const dds::domain::DomainParticipant &participant,
        std::string service_name,
        std::unordered_map<std::string, std::vector<std::string>> link_state)
{
    gazebo_msgs::srv::GetLinkState_Request request(
            link_state["link_name"][0], link_state["reference_frame"][0]);

    gazebo_msgs::srv::GetLinkState_Response reply = send_request<
            gazebo_msgs::srv::GetLinkState_Request,
            gazebo_msgs::srv::GetLinkState_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

void get_model_properties(
        const dds::domain::DomainParticipant &participant,
        std::string service_name,
        std::unordered_map<std::string, std::vector<std::string>>
                model_properties)
{
    gazebo_msgs::srv::GetModelProperties_Request request(
            model_properties["model_name"][0]);

    gazebo_msgs::srv::GetModelProperties_Response reply = send_request<
            gazebo_msgs::srv::GetModelProperties_Request,
            gazebo_msgs::srv::GetModelProperties_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

void get_model_state(
        const dds::domain::DomainParticipant &participant,
        std::string service_name,
        std::unordered_map<std::string, std::vector<std::string>> model_state)
{
    gazebo_msgs::srv::GetModelState_Request request(
            model_state["model_name"][0],
            model_state["relative_entity_name"][0]);

    gazebo_msgs::srv::GetModelState_Response reply = send_request<
            gazebo_msgs::srv::GetModelState_Request,
            gazebo_msgs::srv::GetModelState_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

void set_light_properties(
        const dds::domain::DomainParticipant &participant,
        std::string service_name,
        std::unordered_map<std::string, std::vector<std::string>>
                light_properties)
{
    // Fill the sample
    gazebo_msgs::srv::SetLightProperties_Request request;
    request.light_name(light_properties["light_name"][0]);

    request.diffuse().r(stof(light_properties["diffuse"][0]));
    request.diffuse().g(stof(light_properties["diffuse"][1]));
    request.diffuse().b(stof(light_properties["diffuse"][2]));
    request.diffuse().a(stof(light_properties["diffuse"][3]));

    request.attenuation_constant(
            stof(light_properties["attenuation_constant"][0]));
    request.attenuation_linear(stof(light_properties["attenuation_linear"][0]));
    request.attenuation_quadratic(
            stof(light_properties["attenuation_quadratic"][0]));

    gazebo_msgs::srv::Default_Response reply = send_request<
            gazebo_msgs::srv::SetLightProperties_Request,
            gazebo_msgs::srv::Default_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

void set_link_properties(
        const dds::domain::DomainParticipant &participant,
        std::string service_name,
        std::unordered_map<std::string, std::vector<std::string>>
                link_properties)
{
    // Fill the sample
    gazebo_msgs::srv::SetLinkProperties_Request request;
    request.link_name(link_properties["link_name"][0]);

    request.com().position().x(stof(link_properties["com_position"][0]));
    request.com().position().y(stof(link_properties["com_position"][1]));
    request.com().position().z(stof(link_properties["com_position"][2]));

    request.gravity_mode(
            (strcasecmp("true", link_properties["gravity_mode"][0].c_str())
             == 0));

    request.mass(stof(link_properties["mass"][0]));
    request.ixx(stof(link_properties["ixx"][0]));
    request.ixy(stof(link_properties["ixy"][0]));
    request.ixz(stof(link_properties["ixz"][0]));
    request.iyy(stof(link_properties["iyy"][0]));
    request.iyz(stof(link_properties["iyz"][0]));
    request.izz(stof(link_properties["izz"][0]));

    gazebo_msgs::srv::Default_Response reply = send_request<
            gazebo_msgs::srv::SetLinkProperties_Request,
            gazebo_msgs::srv::Default_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

void set_model_state(
        const dds::domain::DomainParticipant &participant,
        std::string service_name,
        std::unordered_map<std::string, std::vector<std::string>>
                model_state)
{
    // Fill the sample
    gazebo_msgs::srv::SetModelState_Request request;
    request.model_state().model_name(model_state["model_name"][0]);

    request.model_state().pose().position().x(
            stof(model_state["pose_position"][0]));
    request.model_state().pose().position().y(
            stof(model_state["pose_position"][1]));
    request.model_state().pose().position().z(
            stof(model_state["pose_position"][2]));

    request.model_state().pose().orientation().x(
            stof(model_state["pose_orientation"][0]));
    request.model_state().pose().orientation().y(
            stof(model_state["pose_orientation"][1]));
    request.model_state().pose().orientation().z(
            stof(model_state["pose_orientation"][2]));

    request.model_state().twist().linear().x(
            stof(model_state["twist_linear"][0]));
    request.model_state().twist().linear().y(
            stof(model_state["twist_linear"][1]));
    request.model_state().twist().linear().z(
            stof(model_state["twist_linear"][2]));

    request.model_state().twist().angular().x(
            stof(model_state["twist_angular"][0]));
    request.model_state().twist().angular().y(
            stof(model_state["twist_angular"][1]));
    request.model_state().twist().angular().z(
            stof(model_state["twist_angular"][2]));

    request.model_state().reference_frame(model_state["reference_frame"][0]);

    gazebo_msgs::srv::Default_Response reply = send_request<
            gazebo_msgs::srv::SetModelState_Request,
            gazebo_msgs::srv::Default_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

void set_link_state(
        const dds::domain::DomainParticipant &participant,
        std::string service_name,
        std::unordered_map<std::string, std::vector<std::string>>
                link_state)
{
    // Fill the sample
    gazebo_msgs::srv::SetLinkState_Request request;
    request.link_state().link_name(link_state["link_name"][0]);

    request.link_state().pose().position().x(
            stof(link_state["pose_position"][0]));
    request.link_state().pose().position().y(
            stof(link_state["pose_position"][1]));
    request.link_state().pose().position().z(
            stof(link_state["pose_position"][2]));

    request.link_state().pose().orientation().x(
            stof(link_state["pose_orientation"][0]));
    request.link_state().pose().orientation().y(
            stof(link_state["pose_orientation"][1]));
    request.link_state().pose().orientation().z(
            stof(link_state["pose_orientation"][2]));

    request.link_state().twist().linear().x(
            stof(link_state["twist_linear"][0]));
    request.link_state().twist().linear().y(
            stof(link_state["twist_linear"][1]));
    request.link_state().twist().linear().z(
            stof(link_state["twist_linear"][2]));

    request.link_state().twist().angular().x(
            stof(link_state["twist_angular"][0]));
    request.link_state().twist().angular().y(
            stof(link_state["twist_angular"][1]));
    request.link_state().twist().angular().z(
            stof(link_state["twist_angular"][2]));

    request.link_state().reference_frame(link_state["reference_frame"][0]);

    gazebo_msgs::srv::Default_Response reply = send_request<
            gazebo_msgs::srv::SetLinkState_Request,
            gazebo_msgs::srv::Default_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

void send_empty_request(
        const dds::domain::DomainParticipant &participant,
        std::string service_name)
{
    std_msgs::msg::Empty request;

    gazebo_msgs::srv::Default_Response reply = send_request<
            std_msgs::msg::Empty,
            gazebo_msgs::srv::Default_Response>(
            participant, service_name, request);

    std::cout << reply << std::endl;
}

int main(int argc, char *argv[])
{
    int ret_code = 0;

    // Set the unordered_map of functions
    std::unordered_map<
            std::string,
            std::function<void(
                    const dds::domain::DomainParticipant &,
                    const std::string &,
                    const std::unordered_map<
                            std::string,
                            std::vector<std::string>> &)>>
            service_map;

    std::unordered_map<
            std::string,
            std::function<void(
                    const dds::domain::DomainParticipant &,
                    const std::string &)>>
            empty_service_map;

    // Initialize the map of functions
    service_map["delete_model"] = std::bind(
            &delete_model,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    service_map["delete_light"] = std::bind(
            &delete_light,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    service_map["get_light_properties"] = std::bind(
            &get_light_properties,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    service_map["get_joint_properties"] = std::bind(
            &get_joint_properties,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    service_map["get_link_properties"] = std::bind(
            &get_link_properties,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    service_map["get_link_state"] = std::bind(
            &get_link_state,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    service_map["get_model_properties"] = std::bind(
            &get_model_properties,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    service_map["get_model_state"] = std::bind(
            &get_model_state,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    service_map["set_light_properties"] = std::bind(
            &set_light_properties,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    service_map["set_link_properties"] = std::bind(
            &set_link_properties,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    service_map["set_model_state"] = std::bind(
            &set_model_state,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    service_map["set_link_state"] = std::bind(
            &set_link_state,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);

    empty_service_map["get_world_properties"] = std::bind(
            &get_world_properties,
            std::placeholders::_1,
            std::placeholders::_2);

    empty_service_map["reset_simulation"] = std::bind(
            &send_empty_request, std::placeholders::_1, std::placeholders::_2);

    empty_service_map["reset_world"] = std::bind(
            &send_empty_request, std::placeholders::_1, std::placeholders::_2);

    empty_service_map["pause_physics"] = std::bind(
            &send_empty_request, std::placeholders::_1, std::placeholders::_2);

    empty_service_map["unpause_physics"] = std::bind(
            &send_empty_request, std::placeholders::_1, std::placeholders::_2);

    gazebo::dds::utils::CommandLineParser cmd_parser(argc, argv);

    if (cmd_parser.has_flag("-h")) {
        std::cout << "Usage: apipublisher [options]" << std::endl
                  << "Generic options:" << std::endl
                  << "\t-h                      - Prints this page and exits"
                  << std::endl
                  << "\t-d <domain id>          - Sets the domainId (default 0)"
                  << std::endl
                  << "\t-s <service name>       - Sets the service name"
                  << std::endl
                  << "\t-i <sample information> - Sets information of the "
                     "sample"
                  << std::endl;
        return 0;
    }

    // Handle signals (e.g., CTRL+C)
    gazebo::dds::utils::setup_signal_handler();

    try {
        // Check arguments
        int domain_id = 0;
        if (cmd_parser.has_flag("-d")) {
            domain_id = atoi(cmd_parser.get_value("-d").c_str());
        }

        std::string service_name = std::string(cmd_parser.get_value("-s"));

        // Find a DomainParticipant
        dds::domain::DomainParticipant participant(
                dds::domain::find(domain_id));
        if (participant == dds::core::null) {
            participant = dds::domain::DomainParticipant(domain_id);
        }

        // Call the service
        if (cmd_parser.has_flag("-i")) {
            service_map[service_name](
                    participant, service_name, cmd_parser.get_values("-i"));
        } else {
            empty_service_map[service_name](participant, service_name);
        }

    } catch (const std::exception &ex) {
        // This will catch DDS and CommandLineParser exceptions
        std::cerr << ex.what() << std::endl;
        ret_code = -1;
    }

    dds::domain::DomainParticipant::finalize_participant_factory();

    return ret_code;
}