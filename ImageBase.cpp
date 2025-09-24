#include "ImageBase.h"
#include "lodepng.h"

////////////////////////////////// ImageBase ////////////////////////////////////////

ImageBase::ImageBase() : m_height(0), m_width(0), m_valid(true) {}

ImageBase::ImageBase(size_t width, size_t height) : m_height(height), m_width(width), m_valid(true) {}

ImageBase::ImageBase(const std::string& filename) {
	this->load(filename);
}

size_t ImageBase::height() const {
	return m_height;
}

size_t ImageBase::width() const {
	return m_width;
}

size_t ImageBase::size() const {
	return this->width() * this->height();
}

bool ImageBase::valid() const {
	return m_valid;
}

bool ImageBase::on_bounds(size_t column, size_t row) const {
	return row < this->height() && column < this->width();
}

bool ImageBase::same_resolution(const ImageBase& image) const {
	return this->height() == image.height() && this->width() == image.width();
}

void ImageBase::load(const std::string& filename) {

	std::ifstream in_file(filename);
	
	if (!in_file.is_open()) {
		std::cerr << "Error : failure at load while opening file\n";
		return;
	}

	this->load(in_file);
	in_file.close();
}

void ImageBase::save(const std::string& filename) {

	std::ofstream out_file(filename);

	if (!out_file.is_open()) {
		std::cerr << "Error : failure at save while opening file\n";
		return;
	}

	this->save(out_file);
	out_file.close();
}

////////////////////////////////// ImagePGM ////////////////////////////////////////



ImagePGM::ImagePGM(size_t width, size_t height, bool fill) : ImageBase(width, height), m_data(height * width) 
{ 
if(fill)
{std::fill(m_data.begin(), m_data.end(), 255);}
}

void ImagePGM::resize(size_t width, size_t height) {
	return m_data.resize(width * height);
}

OCTET& ImagePGM::operator[](size_t n) {
	return m_data[n];
}

const OCTET& ImagePGM::operator[](size_t n) const {
	return m_data[n];
}

OCTET& ImagePGM::operator()(size_t column, size_t row) {
	return this->m_data[row * this->width() + column]; 
}

const OCTET& ImagePGM::operator()(size_t column, size_t row) const {
	return (*this)(column, row);
}

OCTET* ImagePGM::data() {
	return m_data.data(); 
}

const OCTET* ImagePGM::data() const {
	return m_data.data();
}

ImagePGM::iterator ImagePGM::begin() {
	return this->data();
}

ImagePGM::const_iterator ImagePGM::begin() const {
	return this->begin();
}

ImagePGM::iterator ImagePGM::end() {
	return this->data() + this->size();
}

ImagePGM::const_iterator ImagePGM::end() const {
	return this->end();
}

void ignore_comment(std::istream& is) {
  OCTET c;
  while ((c = is.get()) == '#')
    while ((c = is.get()) != '\n')
   		;
  is.seekg(-sizeof(OCTET), is.cur);
}

void ImagePGM::load(std::istream& is) {
	
	std::string fmt;
	int max_grey_val;
	char dump;

	is >> fmt; //P5
	ignore_comment(is);
	is >> this->m_width >> this->m_height;
	is >> max_grey_val;
	is.read((char*)&dump, 1);
	//is >> dump;
	
	this->m_data.resize(m_height * m_width);

	for(int i = 0; i < m_height * m_width; i++)
		is.read((char*)&this->data()[i], 1);	

//is>>m_data[i];

//	is.read((char*)this->data(), this->size());

	m_valid = is.good();
}

void ImagePGM::save(std::ostream& os) const {

	std::string fmt;

	os << "P5\n";
	os << this->width() << " " << this->height() << "\n";
	os << "255\n";

	for(int i = 0; i < m_height * m_width; i++)
		os.write((char*)&this->data()[i], 1);
	

//os << m_data[i];
//	os.write((char*)this->data(), this->size());

	//os << "\n";
	if (!os.good())
		std::cerr << "Warning : failure at save while writing in file\n";
}

////////////////////////////////// ImagePNG ////////////////////////////////////////

ImagePNG::ImagePNG(const ImagePGM& red, const ImagePGM& green, const ImagePGM& blue, const ImagePGM& alpha) {
	
	if (red.same_resolution(green) && red.same_resolution(blue) && red.same_resolution(alpha)) {
		this->m_red = red;
		this->m_green = green;
		this->m_blue = blue;
		this->m_alpha = alpha;
	}
}

size_t ImagePNG::size() const {
	return this->width() * this->height() * 4;
}

OCTET& ImagePNG::operator[](size_t n) {
	if(n%4 == 0)
		return m_red[n/4];
	if(n%4 == 1)
		return m_green[n/4];
	if(n%4 == 2)
		return m_blue[n/4];
	return m_alpha[n/4];
}

const OCTET& ImagePNG::operator[](size_t n) const {
	if(n%4 == 0)
		return m_red[n/4];
	if(n%4 == 1)
		return m_green[n/4];
	if(n%4 == 2)
		return m_blue[n/4];
	return m_alpha[n/4];
}

OCTET& ImagePNG::operator()(size_t column, size_t row, size_t channel) {
	if(channel == 0)
		return this->m_red[row * this->width() + column];
	if(channel == 1)
		return this->m_green[row * this->width() + column];
	if(channel == 2)
		return this->m_blue[row * this->width() + column];
	return this->m_alpha[row * this->width() + column]; 
}

const OCTET& ImagePNG::operator()(size_t column, size_t row, size_t channel) const {
	return (*this)(column, row, channel);
}

OCTET& ImagePNG::red( size_t column, size_t row) {
	return this->m_red[row * this->width() + column];
}

const OCTET& ImagePNG::red(size_t column, size_t row) const {
	return this->red(column, row);
}

OCTET& ImagePNG::green(size_t column, size_t row) {
	return this->m_green[row * this->width() + column];
}

const OCTET& ImagePNG::green(size_t column, size_t row) const {
	return this->green(column, row);
}

OCTET& ImagePNG::blue(size_t column, size_t row) {
	return this->m_blue[row * this->width() + column];
}

const OCTET& ImagePNG::blue(size_t column, size_t row) const {
	return this->blue(column, row);
}

OCTET& ImagePNG::alpha(size_t column, size_t row) {
	return this->m_alpha[row * this->width() + column];
}

const OCTET& ImagePNG::alpha(size_t column, size_t row) const {
	return this->alpha(column, row);
}

const ImagePGM& ImagePNG::red() const {
	return this->red();
}

const ImagePGM& ImagePNG::green() const {
	return this->green();
}

const ImagePGM& ImagePNG::blue() const {
	return this->blue();
}

const ImagePGM& ImagePNG::alpha() const {
	return this->alpha();
}

void ImagePNG::red(const ImagePGM& red) {
	if (this->same_resolution(red))
		this->m_red = red;
}

void ImagePNG::green(const ImagePGM& green) {
	if (this->same_resolution(green))
		this->m_green = green;
}

void ImagePNG::blue(const ImagePGM& blue) {
	if (this->same_resolution(blue))
		this->m_blue = blue;
}

void ImagePNG::alpha(const ImagePGM& alpha) {
	if (this->same_resolution(alpha))
		this->m_alpha = alpha;
}

void ImagePNG::load(const std::string& filename) {

	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	this->m_width = width;
	this->m_height = height;

  	//if there's an error, display it
  	if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA

	this->m_red.resize(this->width(), this->height());
	this->m_green.resize(this->width(), this->height());
	this->m_blue.resize(this->width(), this->height());
	this->m_alpha.resize(this->width(), this->height());

	for (size_t i = 0 ; i < width*height; ++i) {
		this->m_red[i] = image[i*4];
		this->m_green[i] = image[i*4+1];
		this->m_blue[i] = image[i*4+2];
		this->m_alpha[i] = image[i*4+3];
	}
}

void ImagePNG::save(const std::string& filename) const {
	std::vector<unsigned char>  data(this->width() * this->height() * 4);

	for (size_t i = 0 ; i < this->width() * this->height() ; ++i) {
		data[i*4] = this->m_red[i];
		data[i*4+1] = this->m_green[i];
		data[i*4+2] = this->m_blue[i];
		data[i*4+3] = this->m_alpha[i];
	}

  	//Encode the image
  	unsigned error = lodepng::encode(filename, data, this->width(), this->height());

  	//if there's an error, display it
  	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}


void ImagePNG::load(std::istream& is) {
}

void ImagePNG::save(std::ostream& os) const {
}
