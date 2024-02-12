#include <iostream>
#include <string>

#include "../include/Report.h"

int main() {
  std::string author_name1 = "Васнецов";
  std::string author_name2 = "Репин";
  std::string author_name3 = "Врубель";

  std::string image_name1_1 = "Богатыри";
  std::string image_name1_2 = "Ковер-самолет";
  std::string image_name2_1 = "Садко";
  std::string image_name3_1 = "Демон сидящий";
  std::string image_name3_2 = "Демон летящий";

  std::string museum_name1 = "Третьяковская галерея";

  // creating objects <Image>
  auto p1 = std::make_shared<Image>(Image(author_name1, image_name1_1));
  auto p2 = std::make_shared<Image>(Image(author_name1, image_name1_2));
  auto p3 = std::make_shared<Image>(Image(author_name2, image_name2_1));
  auto p4 = std::make_shared<Image>(Image(author_name3, image_name3_1));
  auto p5 = std::make_shared<Image>(Image(author_name3, image_name3_2));

  // creating object <Museum>
  auto m1 = std::make_shared<Museum>(Museum(museum_name1));

  // transfer of objects <Image> to an object <Museum>
  m1.get()->addImage(p1);
  m1.get()->addImage(p2);
  m1.get()->addImage(p3);
  m1.get()->addImage(p4);
  m1.get()->addImage(p5);

  // creating an object <Report>
  auto r1 = std::make_unique<Report>(author_name1, m1);
  auto report_list = r1.get()->form();
  
  // list of pictures available for transfer
  std::cout << "ОТЧЕТ" << std::endl;
  for (auto image : report_list)
    std::cout << image.get()->getAuthorName() << " " << image.get()->getName() << std::endl;
}
