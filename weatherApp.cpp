#include <iostream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;


int main() {
	cout << "\t+++++++++++++++++++++++++++++++++" << endl;
	cout << "\t\t Whather App" << endl;
	cout << "\t+++++++++++++++++++++++++++++++++" << endl;
	cout << "\t Enter city name : ";
	string city;
	getline(cin, city);
	string city;
	getline(cin, city);

	http_client client(U("https://api.openweathermap.org/data/2.5/weather?q=Pune&appid=ee679ffadb96dd02e8c715b3b4c155ee"));
	url_builder builder(U("/weather"));
	builder.append_query(U("q"), utility::conversions::to_string_t(city));
	builder.append_query(U("appid"), U("ee679ffadb96dd02e8c715b3b4c155ee"));
	http_request request(methods::GET);
	request.set_request_uri(builder.to_string());

	//client.request(request).then([](http_response response) {
	//	return response.extract_json();
		//}

	client.request(request).then([](http_response response) {
		return response.extract_json();
		}).then([](web::json::value body) {
			cout << "\tTemperature: " << body[U("main")][U("temp")].as_double() << " K" << endl;
			cout << "\tHumidity: " << body[U("main")][U("humidity")].as_double() << " %" << endl;
			cout << "\tWeather: " << utility::conversions::to_utf8string(body[U("weather")][0][U("main")].as_string());

			}).wait();
			return 0;


}
