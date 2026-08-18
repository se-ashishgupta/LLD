#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

class ConfigurationMemento
{
private:
    string theme;
    int fontSize;

public:
    ConfigurationMemento(string theme, int fontSize)
    {
        this->theme = theme;
        this->fontSize = fontSize;
    }

    string getTheme()
    {
        return this->theme;
    }

    int getFontSize()
    {
        return this->fontSize;
    }
};

class ApplicationConfiguration
{
private:
    string theme;
    int fontSize;

public:
    ApplicationConfiguration(string theme, int fontSize)
    {
        this->theme = theme;
        this->fontSize = fontSize;
    }

    ConfigurationMemento save()
    {
        cout << "Saving config state" << endl;
        return ConfigurationMemento(theme, fontSize);
    }

    void restore(ConfigurationMemento memento)
    {
        this->theme = memento.getTheme();
        this->fontSize = memento.getFontSize();
        cout << "Restored prev config state" << endl;
    }

    void setTheme(string theme)
    {
        this->theme = theme;
    }

    void setFontSize(int fontSize)
    {
        this->fontSize = fontSize;
    }

    friend ostream &operator<<(ostream &os,
                               const ApplicationConfiguration &config)
    {
        os << "Configuration[Theme=" << config.theme
           << ", Font Size=" << config.fontSize << "]";
        return os;
    }
};

class ConfigurationManager
{
private:
    stack<ConfigurationMemento> history;

public:
    void saveState(ApplicationConfiguration &appConfig)
    {
        ConfigurationMemento memento = appConfig.save();
        history.push(memento);

        cout << "History Saved. History Size: " << this->history.size() << endl;

        if (history.size() == 1)
        {
            cout << "[+] Default State: " << memento.getTheme() << endl;
        }
        else
        {
            cout << "[+] Current State: " << memento.getTheme() << endl;
        }
    }

    void undo(ApplicationConfiguration &appConfig)
    {
        if (history.size() > 1)
        {
            history.pop();

            ConfigurationMemento &mementoToBeRestored = history.top();

            appConfig.restore(mementoToBeRestored);

            cout << "[+] Undo performed. History size: "
                 << history.size() << endl;

            if (history.size() == 1)
            {
                cout << "[+] Default State: "
                     << mementoToBeRestored.getTheme() << endl;
            }
            else
            {
                cout << "[+] Current State: "
                     << mementoToBeRestored.getTheme() << endl;
            }
        }
        else
        {
            cout << "[+] No more states to undo!" << endl;

            if (!history.empty())
            {
                cout << "[+] Default State: " << history.top().getTheme() << endl;
            }
        }
    }
};

int main()
{

    ApplicationConfiguration config("Dark", 14);

    ConfigurationManager manager;

    // Save initial state
    manager.saveState(config);

    // Change 1
    config.setTheme("Light");
    config.setFontSize(16);
    manager.saveState(config);

    // Change 2
    config.setTheme("Blue");
    config.setFontSize(20);
    manager.saveState(config);

    cout << "\nCurrent: " << config << endl;

    // Undo
    manager.undo(config);
    cout << "After Undo: " << config << endl;

    // Undo
    manager.undo(config);
    cout << "After Undo: " << config << endl;

    return 0;
}