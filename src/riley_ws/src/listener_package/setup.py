from setuptools import find_packages, setup

package_name = 'listener_package'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='olympusolutions - riley suomi',
    maintainer_email='suomir@spu.edu',
    description=' TCP listener package',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
                'talker = listener_package.publisher_member_function:main',
                'listener = listener_package.subscriber_member_function:main',
                'phone_listener = listener_package.phone_listener:main',
        ],
    },
)
