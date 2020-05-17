#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto radius = 35;
	auto span = 100;
	auto width = 10;
	auto deg_span = 5;

	for (int x = -span * 3; x <= span * 3; x += span) {

		for (int y = -span * 3; y <= span * 3; y += span) {

			vector<glm::vec2> in_vertices, out_vertices;
			for (int deg = 0; deg < 360; deg += deg_span) {

				in_vertices.push_back(glm::vec2(x + (radius - width * 0.5) * cos(deg * DEG_TO_RAD), y + (radius - width * 0.5) * sin(deg * DEG_TO_RAD)));
				out_vertices.push_back(glm::vec2(x + (radius + width * 0.5) * cos(deg * DEG_TO_RAD), y + (radius + width * 0.5) * sin(deg * DEG_TO_RAD)));

				auto noise_location = glm::vec2(x + (radius + width * 0.5) * cos(deg * DEG_TO_RAD), y + (radius + width * 0.5) * sin(deg * DEG_TO_RAD));
				auto noise_value = ofNoise(noise_location.x * 0.005, noise_location.y * 0.005, ofGetFrameNum() * 0.02);

				if (noise_value < 0.45) {

					vector<glm::vec2> fill_vertices;
					fill_vertices.push_back(glm::vec2(x + (radius - width * 0.5) * cos(deg * DEG_TO_RAD), y + (radius - width * 0.5) * sin(deg * DEG_TO_RAD)));
					fill_vertices.push_back(glm::vec2(x + (radius - width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), y + (radius - width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD)));
					fill_vertices.push_back(glm::vec2(x + (radius + width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), y + (radius + width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD)));
					fill_vertices.push_back(glm::vec2(x + (radius + width * 0.5) * cos(deg * DEG_TO_RAD), y + (radius + width * 0.5) * sin(deg * DEG_TO_RAD)));

					ofFill();
					ofBeginShape();
					ofVertices(fill_vertices);
					ofEndShape(true);
				}
			}

			ofNoFill();

			ofBeginShape();
			ofVertices(in_vertices);
			ofEndShape(true);

			ofBeginShape();
			ofVertices(out_vertices);
			ofEndShape(true);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}