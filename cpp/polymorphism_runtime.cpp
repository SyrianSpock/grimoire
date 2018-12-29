#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// See Sean Parent's talk "Better Code: Runtime Polymorphism"
// https://www.youtube.com/watch?v=QGcVXgEVMJg
class LogEvent
{
public:
    LogEvent() = default;

    LogEvent(const LogEvent&) = delete;
    LogEvent(LogEvent&&) = default;

    template <typename T>
    LogEvent(T&& impl)
          : m_impl(new model_t<typename std::decay<T>::type>(std::forward<T>(impl)))
    {
    }

    LogEvent& operator=(const LogEvent&) = delete;
    LogEvent& operator=(LogEvent&&) = default;

    template <typename T>
    LogEvent& operator=(T&& impl)
    {
        m_impl.reset(new model_t<typename std::decay<T>::type>(std::forward<T>(impl)));
        return *this;
    }

    std::string display() const
    {
        return m_impl->do_display();
    }

private:
    struct concept_t
    {
        virtual ~concept_t()
        {
        }
        virtual std::string do_display() const = 0;
    };
    template <typename T>
    struct model_t : public concept_t
    {
        model_t() = default;
        model_t(const T& v)
              : m_data(v)
        {
        }
        model_t(T&& v)
              : m_data(std::move(v))
        {
        }

        std::string do_display() const override
        {
            return m_data.display();
        }

        T m_data;
    };

    std::unique_ptr<concept_t> m_impl;
};

struct Rectangle
{
    int h;
    int w;

    std::string display() const
    {
        return "Logged rectangle";
    }
};

struct Circle
{
    int r;

    std::string display() const
    {
        return "Logged circle";
    }
};

struct Sprite
{
    std::string path;

    std::string display() const
    {
        return "Logged sprite";
    }
};

int main()
{
    std::vector<LogEvent> logger;

    logger.push_back(Rectangle{12, 42});
    logger.push_back(Circle{10});
    logger.push_back(Sprite{"monster.png"});

    for (const auto& event : logger)
    {
        std::cout << event.display() << std::endl;
    }
}
