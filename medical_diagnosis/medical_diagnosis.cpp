// ============================================================
// Medical Diagnosis - Logistic Regression (One-vs-Rest)
// Constraints: only <iostream> and <fstream>
// Dataset : Symptomsdata.csv  (4920 rows, 41 diseases, 131 symptoms)
// ============================================================

#include <iostream>
#include <fstream>

// ─────────────────────────── constants ───────────────────────────
static const int NUM_SYMPTOMS  = 131;
static const int NUM_CLASSES   = 41;
static const int MAX_ROWS      = 5000;
static const int MAX_COLS      = 19;   // Disease + 17 symptom cols (+1 guard)
static const int MAX_STR       = 128;
static const int TRAIN_RATIO   = 80;   // 80 % train, 20 % test

// ─────────────────────────── lookup tables ───────────────────────
static const char* SYMPTOMS[NUM_SYMPTOMS] = {
    "abdominal_pain","abnormal_menstruation","acidity","acute_liver_failure",
    "altered_sensorium","anxiety","back_pain","belly_pain","blackheads",
    "bladder_discomfort","blister","blood_in_sputum","bloody_stool",
    "blurred_and_distorted_vision","breathlessness","brittle_nails","bruising",
    "burning_micturition","chest_pain","chills","cold_hands_and_feets","coma",
    "congestion","constipation","continuous_feel_of_urine","continuous_sneezing",
    "cough","cramps","dark_urine","dehydration","depression","diarrhoea",
    "dischromic _patches","distention_of_abdomen","dizziness",
    "drying_and_tingling_lips","enlarged_thyroid","excessive_hunger",
    "extra_marital_contacts","family_history","fast_heart_rate","fatigue",
    "fluid_overload","foul_smell_of urine","headache","high_fever",
    "hip_joint_pain","history_of_alcohol_consumption","increased_appetite",
    "indigestion","inflammatory_nails","internal_itching","irregular_sugar_level",
    "irritability","irritation_in_anus","itching","joint_pain","knee_pain",
    "lack_of_concentration","lethargy","loss_of_appetite","loss_of_balance",
    "loss_of_smell","malaise","mild_fever","mood_swings","movement_stiffness",
    "mucoid_sputum","muscle_pain","muscle_wasting","muscle_weakness","nausea",
    "neck_pain","nodal_skin_eruptions","obesity","pain_behind_the_eyes",
    "pain_during_bowel_movements","pain_in_anal_region","painful_walking",
    "palpitations","passage_of_gases","patches_in_throat","phlegm","polyuria",
    "prominent_veins_on_calf","puffy_face_and_eyes","pus_filled_pimples",
    "receiving_blood_transfusion","receiving_unsterile_injections",
    "red_sore_around_nose","red_spots_over_body","redness_of_eyes","restlessness",
    "runny_nose","rusty_sputum","scurring","shivering","silver_like_dusting",
    "sinus_pressure","skin_peeling","skin_rash","slurred_speech",
    "small_dents_in_nails","spinning_movements","spotting_ urination","stiff_neck",
    "stomach_bleeding","stomach_pain","sunken_eyes","sweating","swelled_lymph_nodes",
    "swelling_joints","swelling_of_stomach","swollen_blood_vessels",
    "swollen_extremeties","swollen_legs","throat_irritation","toxic_look_(typhos)",
    "ulcers_on_tongue","unsteadiness","visual_disturbances","vomiting",
    "watering_from_eyes","weakness_in_limbs","weakness_of_one_body_side",
    "weight_gain","weight_loss","yellow_crust_ooze","yellow_urine",
    "yellowing_of_eyes","yellowish_skin"
};

static const char* DISEASES[NUM_CLASSES] = {
    "(vertigo) Paroymsal  Positional Vertigo","AIDS","Acne",
    "Alcoholic hepatitis","Allergy","Arthritis","Bronchial Asthma",
    "Cervical spondylosis","Chicken pox","Chronic cholestasis","Common Cold",
    "Dengue","Diabetes","Dimorphic hemmorhoids(piles)","Drug Reaction",
    "Fungal infection","GERD","Gastroenteritis","Heart attack","Hepatitis B",
    "Hepatitis C","Hepatitis D","Hepatitis E","Hypertension","Hyperthyroidism",
    "Hypoglycemia","Hypothyroidism","Impetigo","Jaundice","Malaria","Migraine",
    "Osteoarthristis","Paralysis (brain hemorrhage)","Peptic ulcer diseae",
    "Pneumonia","Psoriasis","Tuberculosis","Typhoid","Urinary tract infection",
    "Varicose veins","hepatitis A"
};

// ─────────────────────────── tiny string helpers ─────────────────
static int my_strlen(const char* s) {
    int n = 0; while (s[n]) ++n; return n;
}
static void my_strcpy(char* dst, const char* src) {
    int i = 0; while ((dst[i] = src[i])) ++i;
}
static bool my_streq(const char* a, const char* b) {
    int i = 0;
    while (a[i] && b[i] && a[i] == b[i]) ++i;
    return a[i] == '\0' && b[i] == '\0';
}
// strip leading/trailing spaces + trailing \r
static void trim(char* s) {
    int len = my_strlen(s);
    // strip trailing \r \n spaces
    while (len > 0 && (s[len-1] == '\r' || s[len-1] == '\n' || s[len-1] == ' '))
        s[--len] = '\0';
    // strip leading spaces
    int start = 0;
    while (s[start] == ' ') ++start;
    if (start > 0) {
        int i = 0;
        while ((s[i] = s[i + start])) ++i;
    }
}

// ─────────────────────────── math helpers ────────────────────────
static double my_exp(double x) {
    // Taylor series: e^x = sum x^n / n!  (clamped for stability)
    if (x >  500.0) return 1e200;
    if (x < -500.0) return 0.0;
    double result = 1.0, term = 1.0;
    for (int n = 1; n <= 100; ++n) {
        term *= x / n;
        result += term;
        if (term < 1e-15 && term > -1e-15) break;
    }
    return result;
}
static double sigmoid(double z) {
    return 1.0 / (1.0 + my_exp(-z));
}
static double my_sqrt(double x) {
    if (x <= 0.0) return 0.0;
    double g = x * 0.5;
    for (int i = 0; i < 60; ++i) g = 0.5 * (g + x / g);
    return g;
}

// ─────────────────────────── dataset storage ─────────────────────
// X[row][symptom] = 0/1 binary feature
// y[row] = class index (0-40)
static double X[MAX_ROWS][NUM_SYMPTOMS];
static int    y[MAX_ROWS];
static int    total_rows = 0;

// ─────────────────────────── CSV parsing ─────────────────────────
static int symptom_index(const char* name) {
    for (int i = 0; i < NUM_SYMPTOMS; ++i)
        if (my_streq(name, SYMPTOMS[i])) return i;
    return -1;
}
static int disease_index(const char* name) {
    for (int i = 0; i < NUM_CLASSES; ++i)
        if (my_streq(name, DISEASES[i])) return i;
    return -1;
}

// split a CSV line into fields (handles up to MAX_COLS fields)
static int split_csv(char* line, char fields[][MAX_STR], int max_fields) {
    int col = 0, ci = 0;
    for (int i = 0; line[i] != '\0' && col < max_fields; ++i) {
        if (line[i] == ',') {
            fields[col][ci] = '\0';
            trim(fields[col]);
            ++col; ci = 0;
        } else {
            if (ci < MAX_STR - 1) fields[col][ci++] = line[i];
        }
    }
    // last field
    fields[col][ci] = '\0';
    trim(fields[col]);
    return col + 1;
}

static bool load_csv(const char* path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cerr << "ERROR: cannot open " << path << "\n";
        return false;
    }
    char line[4096];
    // skip header
    fin.getline(line, sizeof(line));

    total_rows = 0;
    char fields[MAX_COLS][MAX_STR];

    while (fin.getline(line, sizeof(line))) {
        if (total_rows >= MAX_ROWS) break;
        int ncols = split_csv(line, fields, MAX_COLS);
        if (ncols < 1) continue;

        // disease
        int di = disease_index(fields[0]);
        if (di < 0) continue;   // unknown disease – skip
        y[total_rows] = di;

        // zero out features
        for (int j = 0; j < NUM_SYMPTOMS; ++j) X[total_rows][j] = 0.0;

        // symptoms (columns 1..ncols-1)
        for (int c = 1; c < ncols; ++c) {
            if (fields[c][0] == '\0') continue;
            int si = symptom_index(fields[c]);
            if (si >= 0) X[total_rows][si] = 1.0;
        }
        ++total_rows;
    }
    fin.close();
    std::cout << "Loaded " << total_rows << " rows.\n";
    return true;
}

// ─────────────────────────── train / test split ───────────────────
static int train_idx[MAX_ROWS], test_idx[MAX_ROWS];
static int n_train = 0, n_test = 0;

// Simple deterministic split: every 5th sample → test
static void split_data() {
    n_train = n_test = 0;
    for (int i = 0; i < total_rows; ++i) {
        if ((i % 5) == 4) test_idx [n_test++]  = i;
        else              train_idx[n_train++] = i;
    }
    std::cout << "Train: " << n_train << "  Test: " << n_test << "\n";
}

// ─────────────────────────── model weights ───────────────────────
// OvR: one weight vector per class
// W[class][symptom],  b[class]
static double W[NUM_CLASSES][NUM_SYMPTOMS];
static double b[NUM_CLASSES];

static void init_weights() {
    for (int c = 0; c < NUM_CLASSES; ++c) {
        b[c] = 0.0;
        for (int j = 0; j < NUM_SYMPTOMS; ++j) W[c][j] = 0.0;
    }
}

// ─────────────────────────── training ────────────────────────────
static void train(double lr, int epochs) {
    std::cout << "\nTraining OvR Logistic Regression...\n";
    std::cout << "  LR=" << lr << "  Epochs=" << epochs << "\n\n";

    for (int c = 0; c < NUM_CLASSES; ++c) {
        // binary target: 1 if y==c, else 0
        for (int ep = 0; ep < epochs; ++ep) {
            double dW[NUM_SYMPTOMS] = {};
            double db_val = 0.0;

            for (int ii = 0; ii < n_train; ++ii) {
                int r  = train_idx[ii];
                int yc = (y[r] == c) ? 1 : 0;

                // z = W·x + b
                double z = b[c];
                for (int j = 0; j < NUM_SYMPTOMS; ++j)
                    z += W[c][j] * X[r][j];

                double pred  = sigmoid(z);
                double error = pred - yc;

                // accumulate gradients
                db_val += error;
                for (int j = 0; j < NUM_SYMPTOMS; ++j)
                    dW[j] += error * X[r][j];
            }

            // gradient descent update (batch / full GD)
            double inv_n = 1.0 / n_train;
            b[c] -= lr * db_val * inv_n;
            for (int j = 0; j < NUM_SYMPTOMS; ++j)
                W[c][j] -= lr * dW[j] * inv_n;
        }

        // progress every 5 classes
        if ((c + 1) % 5 == 0 || c == NUM_CLASSES - 1)
            std::cout << "  Trained " << (c+1) << "/" << NUM_CLASSES << " classifiers\n";
    }
    std::cout << "Training complete.\n\n";
}

// ─────────────────────────── prediction ──────────────────────────
// Returns class with highest sigmoid score
static int predict(const double* x) {
    int best_c = 0;
    double best_s = -1e300;
    for (int c = 0; c < NUM_CLASSES; ++c) {
        double z = b[c];
        for (int j = 0; j < NUM_SYMPTOMS; ++j) z += W[c][j] * x[j];
        double s = sigmoid(z);
        if (s > best_s) { best_s = s; best_c = c; }
    }
    return best_c;
}

// ─────────────────────────── evaluation ──────────────────────────
static void evaluate() {
    int correct = 0;
    // per-class TP / FP / FN
    int TP[NUM_CLASSES] = {}, FP[NUM_CLASSES] = {}, FN[NUM_CLASSES] = {};

    for (int ii = 0; ii < n_test; ++ii) {
        int r    = test_idx[ii];
        int pred = predict(X[r]);
        int gt   = y[r];
        if (pred == gt) { ++correct; ++TP[gt]; }
        else            { ++FP[pred]; ++FN[gt]; }
    }

    double acc = (n_test > 0) ? 100.0 * correct / n_test : 0.0;
    std::cout << "=== Evaluation on Test Set ===\n";
    std::cout << "Accuracy : " << (int)acc << "." << (int)(acc*10)%10 << "%"
              << "  (" << correct << "/" << n_test << ")\n\n";

    // macro F1
    double macro_f1 = 0.0;
    std::cout << "Per-class Precision / Recall / F1:\n";
    for (int c = 0; c < NUM_CLASSES; ++c) {
        double prec = (TP[c]+FP[c] > 0) ? 1.0*TP[c]/(TP[c]+FP[c]) : 0.0;
        double rec  = (TP[c]+FN[c] > 0) ? 1.0*TP[c]/(TP[c]+FN[c]) : 0.0;
        double f1   = (prec+rec > 0) ? 2*prec*rec/(prec+rec) : 0.0;
        macro_f1   += f1;
        // truncate disease name for display
        char name[40];
        int len = my_strlen(DISEASES[c]);
        if (len > 35) { my_strcpy(name, "..."); }
        else           { my_strcpy(name, DISEASES[c]); }
        std::cout << "  [" << c << "] ";
        // pad name to 40 chars
        std::cout << name;
        for (int p = my_strlen(name); p < 38; ++p) std::cout << ' ';
        // print metrics as percentages (integer %)
        std::cout << "P=" << (int)(prec*100) << "%  "
                  << "R=" << (int)(rec*100)  << "%  "
                  << "F1=" << (int)(f1*100) << "%\n";
    }
    macro_f1 /= NUM_CLASSES;
    std::cout << "\nMacro F1: " << (int)(macro_f1*100) << "%\n\n";
}

// ─────────────────────────── weight saving ───────────────────────
static bool save_weights(const char* path) {
    std::ofstream fout(path);
    if (!fout.is_open()) { std::cerr << "Cannot write " << path << "\n"; return false; }
    fout << NUM_CLASSES << " " << NUM_SYMPTOMS << "\n";
    for (int c = 0; c < NUM_CLASSES; ++c) {
        fout << b[c];
        for (int j = 0; j < NUM_SYMPTOMS; ++j) fout << " " << W[c][j];
        fout << "\n";
    }
    fout.close();
    std::cout << "Weights saved to " << path << "\n";
    return true;
}
static bool load_weights(const char* path) {
    std::ifstream fin(path);
    if (!fin.is_open()) return false;
    int nc, ns; fin >> nc >> ns;
    if (nc != NUM_CLASSES || ns != NUM_SYMPTOMS) return false;
    for (int c = 0; c < NUM_CLASSES; ++c) {
        fin >> b[c];
        for (int j = 0; j < NUM_SYMPTOMS; ++j) fin >> W[c][j];
    }
    fin.close();
    std::cout << "Weights loaded from " << path << "\n";
    return true;
}

// ─────────────────────────── interactive mode ────────────────────
static void interactive_predict() {
    std::cout << "\n=== Interactive Diagnosis Mode ===\n";
    std::cout << "Enter symptoms separated by commas (or 'quit' to exit).\n";
    std::cout << "Example: itching,skin_rash,fatigue\n\n";

    char line[2048];
    while (true) {
        std::cout << "> ";
        std::cin.getline(line, sizeof(line));
        trim(line);
        if (my_streq(line, "quit") || my_streq(line, "exit")) break;
        if (line[0] == '\0') continue;

        // build feature vector
        double xv[NUM_SYMPTOMS] = {};

        // tokenise by comma
        char token[MAX_STR]; int ti = 0;
        int found = 0, unknown = 0;
        for (int i = 0; ; ++i) {
            char ch = line[i];
            if (ch == ',' || ch == '\0') {
                token[ti] = '\0'; trim(token); ti = 0;
                if (token[0] != '\0') {
                    int si = symptom_index(token);
                    if (si >= 0) { xv[si] = 1.0; ++found; }
                    else { std::cout << "  Unknown symptom: '" << token << "'\n"; ++unknown; }
                }
                if (ch == '\0') break;
            } else {
                if (ti < MAX_STR-1) token[ti++] = ch;
            }
        }

        if (found == 0) { std::cout << "No recognised symptoms.\n\n"; continue; }

        // top-3 predictions
        // compute scores
        double scores[NUM_CLASSES];
        for (int c = 0; c < NUM_CLASSES; ++c) {
            double z = b[c];
            for (int j = 0; j < NUM_SYMPTOMS; ++j) z += W[c][j] * xv[j];
            scores[c] = sigmoid(z);
        }
        // sort top 3 (simple selection)
        int order[3] = {-1,-1,-1};
        double used[NUM_CLASSES] = {};
        for (int ii = 0; ii < NUM_CLASSES; ++ii) used[ii] = scores[ii];
        for (int t = 0; t < 3; ++t) {
            double best = -1.0; int bi = 0;
            for (int c = 0; c < NUM_CLASSES; ++c)
                if (used[c] > best) { best = used[c]; bi = c; }
            order[t] = bi;
            used[bi] = -1.0;
        }

        std::cout << "\nRecognised " << found << " symptom(s)";
        if (unknown) std::cout << " (" << unknown << " unknown)";
        std::cout << ".\nTop predictions:\n";
        for (int t = 0; t < 3; ++t) {
            int c = order[t];
            int pct = (int)(scores[c] * 100);
            std::cout << "  " << (t+1) << ". " << DISEASES[c]
                      << "  (score: " << pct << "%)\n";
        }
        std::cout << "\n";
    }
}

// ─────────────────────────── main ────────────────────────────────
int main(int argc, char* argv[]) {
    const char* csv_path     = "Symptomsdata.csv";
    const char* weights_path = "weights.txt";
    double lr    = 0.1;
    int    epochs = 200;

    // allow: ./medical_diagnosis [csv_path] [lr] [epochs]
    if (argc >= 2) csv_path = argv[1];
    if (argc >= 3) {
        // parse lr manually
        double v = 0.0; bool after = false;
        double frac = 0.1;
        for (int i = 0; argv[2][i]; ++i) {
            char c = argv[2][i];
            if (c == '.') { after = true; }
            else if (c >= '0' && c <= '9') {
                if (!after) v = v*10 + (c-'0');
                else        { v += (c-'0')*frac; frac *= 0.1; }
            }
        }
        if (v > 0.0) lr = v;
    }
    if (argc >= 4) {
        int v = 0;
        for (int i = 0; argv[3][i]; ++i)
            if (argv[3][i] >= '0' && argv[3][i] <= '9') v = v*10 + (argv[3][i]-'0');
        if (v > 0) epochs = v;
    }

    std::cout << "Medical Diagnosis System - Logistic Regression (OvR)\n";
    std::cout << "======================================================\n\n";

    // ── load data ──────────────────────────────────────────────
    if (!load_csv(csv_path)) return 1;
    split_data();

    // ── train or load weights ──────────────────────────────────
    init_weights();

    // attempt to load pre-saved weights; train if not found
    if (!load_weights(weights_path)) {
        train(lr, epochs);
        save_weights(weights_path);
    }

    // ── evaluate ───────────────────────────────────────────────
    evaluate();

    // ── interactive ────────────────────────────────────────────
    interactive_predict();

    return 0;
}