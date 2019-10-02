#include <iostream>
#include <random>
#include <vector>

class Perceptron {

    /*
     * Nachfolgende Attribute und Methoden, sind private und für den Anwender unwichtig.
     */
private:
    std::vector<double> w;
    int iterations;

    std::vector<double> mul(std::vector<double> v, double s) {
        for(int i = 0; i < v.size(); i++) {
            v.at(i) *= s;
        }

        return v;
    }

    std::vector<double> add(std::vector<double> v1, std::vector<double> v2) {

        for(int i = 0; i < v1.size(); i++) {
            v1.at(i) += v2.at(i);
        }

        return v1;
    }

    double dot(std::vector<double> v1, std::vector<double> v2) {

        double erg = 0;

        for(int i = 0; i < v1.size(); i++) {
            erg += v1.at(i) * v2.at(i);
        }

        return erg;
    }

    int getRandIndex(int max) {
        std::random_device rd;
        std::mt19937 engine(rd());

        std::uniform_int_distribution<int> dice(0, max);

        return dice(engine);
    }

    double heavside(double x) {
        if(x <= 0) {
            return 0;
        }
        else {
            return 1;
        }
    }

    /*
     * Nachfolgende Methoden sind public und für die öffentliche Verwendung geeignet.
     */
public:

    /*
     * Konstruktor. In den Klammern werden die Anzahl der Iterationen für das Lernen angegeben.
     */
    Perceptron(int iterations) {
        w = { 0, 0, 0 };
        this->iterations = iterations;
    }

    /*
     * Methode zum Lernen des Perceptrons.
     * training_data als zweidimensionales Array, das die Trainingsdatensätze enthält.
     * results als Array, das die gewünschte Ergebnisse zu den jeweiligen Trainingsdatensätzen enthält.
     *
     * Die Anzahl der Elemente in den Arrays sollten gleich sein. Dies wird nicht überprüft.
     */
    std::vector<double> fit(std::vector<std::vector<double>> training_data, std::vector<double> results) {
        std::vector<double> x;
        int y = 0;
        double o = 0.0;
        double error = 0.0;

        for(int i = 0; i < iterations; i++) {
            int index = this->getRandIndex(training_data.size()-1);
            x = training_data.at(index);
            y = results.at(index);

            o = this->heavside(this->dot(x, w));
            error = y - o;

            w = this->add(w, this->mul(x, error));
        }

        return w;
    }

    /*
     * Auswertungsmethode. Inputvektor wird ausgewertet. Es wird nicht geprüft, ob die Methode fit schon aufgerufen wurde.
     */
    double predict(std::vector<double> x) {

        return heavside(dot(x, w));
    }
};

int main() {
    // Hier ein Beispiel für das zweidimensionale Array, welches die Trainingsdatensätze enthält
    std::vector<std::vector<double>> X = {
        { 1, 0, 0 },
        { 1, 0, 1 },
        { 1, 1, 0 },
        { 1, 1, 1 }
    };

    // Hier ein Beispiel für das "results" Array, welche die gewünschten Ergebnisse beinhaltet. {1, 0, 0} -> 0 ; {1, 0, 1} -> 0 ; {1, 1, 0} -> 0 ; {1, 1, 1} -> 1
    std::vector<double> y = { 0, 0, 0, 1 };

    // Ein Perceptron, dass für das Lernen mit 50 Iterationen initialisiert wurde
    Perceptron p = Perceptron(50);

    // Gewichtsvektor für nach dem Lernen
    std::vector<double> w;

    // Das Lernen, die Parameter sind erstens die Trainingsdatensätze und zweitens die gewünschten Ergebnisse
    w = p.fit(X, y);


    // Hier die Ausgabe des Gewichtsvektors nach dem Lernen
    std::cout << "Gewichtsvektor nach dem Lernen: " << std::endl;
    std::cout << "( ";
    for(int i = 0; i < w.size(); i++) {
        std::cout << w.at(i) << ", ";
    }
    std::cout << " )" << std::endl;

    return 0;
}
