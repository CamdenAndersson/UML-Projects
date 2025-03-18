// Copyright 2024 Camden Andersson
#include <iostream>
#include <fstream>
#include "Sokoban.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

using SB::Sokoban;

BOOST_AUTO_TEST_CASE(testInstantWin) {
  std::ifstream file;
  file.open("level1.lvl");
  SB::Sokoban sb;
  file >> sb;
  BOOST_REQUIRE_EQUAL(false, sb.isWon());
}

BOOST_AUTO_TEST_CASE(testCantMove) {
  std::ifstream file;
  file.open("level1.lvl");
  SB::Sokoban sb;
  file >> sb;
  sb.movePlayer(SB::Direction::Right);
  int startX = sb.playerLoc().x;
  int startY = sb.playerLoc().y;
  sb.movePlayer(SB::Direction::Up);
  int endX = sb.playerLoc().x;
  int endY = sb.playerLoc().y;
  BOOST_REQUIRE_EQUAL(startX, endX);
  BOOST_REQUIRE_EQUAL(startY, endY);
}

BOOST_AUTO_TEST_CASE(testBoxWall) {
  std::ifstream file;
  file.open("level3.lvl");
  SB::Sokoban sb;
  file >> sb;
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  int startX = sb.playerLoc().x;
  int startY = sb.playerLoc().y;
  sb.movePlayer(SB::Direction::Right);
  int endX = sb.playerLoc().x;
  int endY = sb.playerLoc().y;
  BOOST_REQUIRE_EQUAL(startX, endX);
  BOOST_REQUIRE_EQUAL(startY, endY);
}

BOOST_AUTO_TEST_CASE(testBoxBox) {
  std::ifstream file;
  file.open("level2.lvl");
  SB::Sokoban sb;
  file >> sb;
  int startX = sb.playerLoc().x;
  int startY = sb.playerLoc().y;
  sb.movePlayer(SB::Direction::Up);
  int endX = sb.playerLoc().x;
  int endY = sb.playerLoc().y;
  BOOST_REQUIRE_EQUAL(startX, endX);
  BOOST_REQUIRE_EQUAL(startY, endY);
}

BOOST_AUTO_TEST_CASE(testMoveOffScreen) {
  std::ifstream file;
  file.open("level4.lvl");
  SB::Sokoban sb;
  file >> sb;
  sb.movePlayer(SB::Direction::Down);
  sb.movePlayer(SB::Direction::Down);
  sb.movePlayer(SB::Direction::Down);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  int startX = sb.playerLoc().x;
  int startY = sb.playerLoc().y;
  sb.movePlayer(SB::Direction::Right);
  int endX = sb.playerLoc().x;
  int endY = sb.playerLoc().y;
  BOOST_REQUIRE_EQUAL(startX, endX);
  BOOST_REQUIRE_EQUAL(startY, endY);
}

BOOST_AUTO_TEST_CASE(testMoreBoxes) {
  std::ifstream file;
  file.open("level5.lvl");
  SB::Sokoban sb;
  file >> sb;
  sb.movePlayer(SB::Direction::Up);
  sb.movePlayer(SB::Direction::Up);
  sb.movePlayer(SB::Direction::Up);
  sb.movePlayer(SB::Direction::Up);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Down);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Up);
  BOOST_REQUIRE_EQUAL(true, sb.isWon());
}

BOOST_AUTO_TEST_CASE(testMoreStorage) {
  std::ifstream file;
  file.open("level6.lvl");
  SB::Sokoban sb;
  file >> sb;
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Up);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Up);
  sb.movePlayer(SB::Direction::Right);
  sb.movePlayer(SB::Direction::Down);
  sb.movePlayer(SB::Direction::Up);
  sb.movePlayer(SB::Direction::Up);
  sb.movePlayer(SB::Direction::Up);
  sb.movePlayer(SB::Direction::Left);
  sb.movePlayer(SB::Direction::Left);
  sb.movePlayer(SB::Direction::Left);
  sb.movePlayer(SB::Direction::Left);
  sb.movePlayer(SB::Direction::Down);
  sb.movePlayer(SB::Direction::Left);
  sb.movePlayer(SB::Direction::Up);
  BOOST_REQUIRE_EQUAL(true, sb.isWon());
}





