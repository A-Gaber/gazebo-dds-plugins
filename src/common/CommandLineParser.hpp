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

#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

namespace gazebo { namespace dds { namespace utils {

class CommandLineParser {
public:
    /**
     * @brief Constructor
     */
    CommandLineParser(int argc, char *argv[])
    {
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-' && i + 1 < argc && argv[i + 1][0] != '-') {
                argument_map_.insert(std::pair<std::string, std::string>(
                        argv[i], argv[i + 1]));
            } else if (argv[i][0] == '-') {
                argument_map_.insert(
                        std::pair<std::string, std::string>(argv[i], ""));
            }
        }
    }

    /**
     * @brief Destructor
     */
    ~CommandLineParser()
    {
    }

    /**
     * @brief Get value of a specific key
     *
     * @param key_value key that will be looked for on the map.
     * @return string that contains the value of the key
     */
    std::string get_value(std::string key_value)
    {
        if (argument_map_.find(key_value) == argument_map_.end()) {
            throw std::runtime_error(
                    std::string("CommandLineParser: Error in parameter '")
                    + key_value + "'");
        } else if (argument_map_[key_value] == "" && key_value != "-h") {
            throw std::runtime_error(
                    std::string(
                            "CommandLineParser: Missing value for argument '")
                    + key_value + "'");
        }

        return argument_map_[key_value];
    }

    /**
     * @brief Get the values of a specific key
     *
     * @param key_value key that will be looked for on the map.
     * @return map that contains all the values of the key
     */
    std::unordered_map<std::string, std::vector<std::string>>
            get_values(std::string key_value)
    {
        std::string values = get_value(key_value);

        // Process values
        std::size_t found;
        found = values.find("(");
        if (found != std::string::npos)
            values.erase(found, 1);

        found = values.find(")");
        if (found != std::string::npos)
            values.erase(found, 1);

        process_values(values);

        std::istringstream buffer(values);
        std::istream_iterator<std::string> it_begin(buffer), it_end;

        std::vector<std::string> value_list(it_begin, it_end);

        // Set the unordered_map
        std::unordered_map<std::string, std::vector<std::string>> result_map;

        std::string current_variable;
        for (int i = 0; i < value_list.size(); i++) {
            if (value_list[i][value_list[i].size() - 1] == ':') {
                current_variable = value_list[i].substr(0, value_list[i].size() - 1);
            } else {
                result_map[current_variable].push_back(value_list[i]);
            }
        }

        return result_map;
    }

    /**
     * @brief Check if the key exist
     *
     * @param key_value key that will be checked.
     * @return if the key exist or not
     */
    bool has_flag(std::string key_value)
    {
        bool result = false;

        if (argument_map_.find(key_value) != argument_map_.end()) {
            result = true;
        }

        return result;
    }

private:
    /**
     * @brief Process the raw data to format them correctly
     *
     * @param data the raw data that will be processed.
     */
    void process_values(std::string &data)
    {
        std::size_t index = data.find(":");
        while (index < std::string::npos) {
            if (data[index + 1] != ' ') {
                data.insert(index + 1, " ");
            }

            index = data.find(":", index + 1);
        }
    }

private:
    std::map<std::string, std::string> argument_map_;
};

}  // namespace utils
}  // namespace dds
}  // namespace gazebo

#endif  // COMMAND_LINE_PARSER_HPP
