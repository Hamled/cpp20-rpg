#include <iostream>

#include <spdlog/spdlog.h>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iterator>
#include <range/v3/view/zip.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/iterator/unreachable_sentinel.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv)
{
  //Use the default logger (stdout, multi-threaded, colored)
  spdlog::info("Starting ImGui + SFML");

  sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  // Set ImGui scale
  constexpr auto scale_factor = 2.0;
  ImGui::GetStyle().ScaleAllSizes(scale_factor);
  ImGui::GetIO().FontGlobalScale = scale_factor;

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());

//    ImGui::ShowDemoWindow();

    ImGui::Begin("The Plan");
    {
      using ranges::views::zip;
      using ranges::views::ints;

      auto plan_items = {
        "The Plan",
        "Getting Started",
        "Finding Errors As Soon As Possible",
        "Handling Command Line Parameters",
        "C++ 20 So Far",
        "Reading SFML Input States",
        "Managing Game State",
        "Making Our Game Testable",
        "Making Game State Allocator-Aware",
        "Add Logging To Game Engine",
        "Draw A Game Map",
        "Dialog Trees",
        "Porting from SFML to SDL"
      };
      auto CURRENT_STEP = 3U;
      for(auto &&[item, index] : zip(plan_items, ints(0u, ranges::unreachable)))
      {
        std::string text = std::to_string(index);
        text += " : ";
        text += item;

        auto checked = index < CURRENT_STEP;
        ImGui::Checkbox(text.c_str(), &checked);
      }
    }
    ImGui::End();

    window.clear();
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
