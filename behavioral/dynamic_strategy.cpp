//
// Created by Alexander Chekh on 19.08.2018.
//

#include "behavioral.h"

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

namespace Strategy {

  enum class OutputFormat {
      markdown,
      html
  };

  struct PrintListStrategy {
      virtual void start(ostringstream &oss) {}

      virtual void end(ostringstream &oss) {}

      virtual void addItem(ostringstream &oss, const string &item) = 0;
  };

  struct MarkdownPrintListStrategy : public PrintListStrategy {
      void addItem(ostringstream &oss, const string &item) override {
          oss << "* " << item << "\n";
      }
  };

  struct HtmlPrintListStrategy : public PrintListStrategy {
      void start(ostringstream &oss) override {
          oss << "<ul>\n";
      }

      void addItem(ostringstream &oss, const string &item) override {
          oss << "  " << "<li>" << item << "</li>" << "\n";
      }

      void end(ostringstream &oss) override {
          oss << "</ul>\n";
      }
  };

  class DynamicTextProcessor {
  public:
      void clean() {
          oss.clear();
      }

      void setOutputFormat(const OutputFormat &format) {
          switch (format) {
              case OutputFormat::markdown:
                  printListStrategy = make_unique<MarkdownPrintListStrategy>();
                  break;
              case OutputFormat::html:
                  printListStrategy = make_unique<HtmlPrintListStrategy>();
                  break;
          }
      }

      void appendList(const vector<string> &items) {
          printListStrategy->start(oss);
          for (const auto &item : items) {
              printListStrategy->addItem(oss, item);
          }
          printListStrategy->end(oss);
      }

      string str() const {
          return oss.str();
      }

  private:
      ostringstream oss;
      unique_ptr<PrintListStrategy> printListStrategy;
  };

  template <typename PLS>
  class StaticTextProcessor {
  public:
      void clean() {
          oss.clear();
      }

      void appendList(const vector<string> &items) {
          printListStrategy.start(oss);
          for (const auto &item : items) {
              printListStrategy.addItem(oss, item);
          }
          printListStrategy.end(oss);
      }

      string str() const {
          return oss.str();
      }

  private:
      ostringstream oss;
      PLS printListStrategy;
  };

}

void behavioral_example10() {
    Strategy::DynamicTextProcessor textProcessor;

    textProcessor.setOutputFormat(Strategy::OutputFormat::markdown);
    textProcessor.appendList({"foo", "bar", "biz"});
    cout << textProcessor.str() << "\n";

    Strategy::StaticTextProcessor<Strategy::HtmlPrintListStrategy> staticTextProcessor;
    staticTextProcessor.appendList({"foo", "bar", "biz"});
    cout << staticTextProcessor.str() << "\n";
}
